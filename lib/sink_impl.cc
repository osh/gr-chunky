/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "sink_impl.h"

namespace gr {
  namespace chunky {

    sink::sptr
    sink::make(int maxlen)
    {
      return gnuradio::get_initial_sptr
        (new sink_impl(maxlen));
    }

    sink_impl::sink_impl(int maxlen)
      : gr::block("sink",
              gr::io_signature::make(0,1, sizeof(float)),
              gr::io_signature::make(0,0,0)),
        d_nitems(0), d_npkts(0), d_ts(0)
    {
        message_port_register_in(pmt::mp("pdus"));
        set_msg_handler(pmt::mp("pdus"),
            boost::bind(&sink_impl::handler, this, _1));
    }

    sink_impl::~sink_impl()
    {
    }

    void
    sink_impl::handler(pmt::pmt_t pdu)
    {
        pmt::pmt_t meta = pmt::car(pdu);
        pmt::pmt_t vec = pmt::cdr(pdu);
        work_chunk( meta, gr_vector_int(1,pmt::length(vec)), gr_vector_const_void_star(1,pmt::blob_data(vec)) );
    }
    
    int
    sink_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        std::vector<tag_t> tags;
        get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+1);
        //get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+1);
        if(tags.size() == 0){
            throw std::runtime_error("expected stream tag ....\n");
            }
        int len = -1;
        pmt::pmt_t dict = pmt::make_dict();
        for(int i=0; i<tags.size(); i++){
            dict = pmt::dict_add(dict, tags[i].key, tags[i].value);
            if(pmt::eqv(tags[i].key, pmt::mp("packet_len"))){
                len = pmt::to_long(tags[i].value);
                }
            }
        if(len <= 0 || len > ninput_items[0]){
            throw std::runtime_error("stream block size out of range\n");
            }

        work_chunk( dict, gr_vector_int(1,len), gr_vector_const_void_star(1,input_items[0]) );
        consume_each(len);
        return len;
    }

    void 
    sink_impl::work_chunk(pmt::pmt_t meta, gr_vector_int ninput_items, gr_vector_const_void_star input_items)
    {
        d_npkts ++;
        d_nitems += ninput_items[0];

        int update_modulo = 10000;
        int seq = pmt::to_uint64(pmt::dict_ref(meta, pmt::mp("seq"), pmt::PMT_NIL));

        if(seq % update_modulo == 0){
        boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
        int tx_time = pmt::to_uint64(pmt::dict_ref(meta, pmt::mp("time"), pmt::PMT_NIL));
        int rx_time = mst1.time_of_day().total_microseconds();
        int latency_us = rx_time - tx_time;

        if(d_ts == 0){
            d_ts = rx_time;
        } else {
            float tp_items = d_nitems*1e6/(rx_time-d_ts);
            float tp_pkts = d_npkts*1e6/(rx_time-d_ts);
            printf("%d,%d,%d,%f,%f\n", seq, rx_time, latency_us, tp_items, tp_pkts);
            }
        }
    }

  }
}

