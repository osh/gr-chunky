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
#include "source_impl.h"

namespace gr {
  namespace chunky {

    source::sptr
    source::make(int min, int max)
    {
      return gnuradio::get_initial_sptr
        (new source_impl(min, max));
    }

    source_impl::source_impl(int min, int max)
      : gr::sync_block("source",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,1,sizeof(float))),
        d_min(min), d_max(max), d_done(false), d_seq(0)
    {
        message_port_register_out(pmt::mp("pdus"));
        set_output_multiple(d_max);
    }

    source_impl::~source_impl()
    {
    }

    void source_impl::thread_body()
    {
        while(!d_done){
            handler(pmt::PMT_NIL);
            }
    }

    bool 
    source_impl::start()
    {
        if(pmt::length( message_subscribers(pmt::mp("pdus")) ) > 0)
            d_thread = boost::thread( boost::bind(&source_impl::thread_body, this) );
        return true;
    }

    bool 
    source_impl::stop()
    {
        d_done = true;
        if(pmt::length( message_subscribers(pmt::mp("pdus")) ) > 0)
            d_thread.join();
        return true;
    }

    int
    source_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = d_max;
      return noutput_items ;
    }

    int
    source_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {   
        if(output_items.size() > 0){
            std::pair<pmt::pmt_t, int> p = work_chunk(d_max, output_items);
            add_item_tag( 0, nitems_written(0), pmt::mp("packet_len"), pmt::from_long(p.second), pmt::PMT_NIL );

            // set metadata 
            for( pmt::pmt_t kl = pmt::dict_keys(p.first); 
                    !pmt::eq(kl, pmt::PMT_NIL);
                    kl = pmt::cdr(kl) ){
                    pmt::pmt_t k = pmt::car(kl);
                    pmt::pmt_t v = pmt::dict_ref(p.first, k, pmt::PMT_NIL);
                    add_item_tag( 0, nitems_written(0), k, v );
            }

            return p.second;
        }
        return 0;
    }

    void
    source_impl::handler(pmt::pmt_t msg)
    {
        pmt::pmt_t vec = pmt::make_f32vector(d_max, 0);
        size_t arg;
        std::pair<pmt::pmt_t, int> p = work_chunk(d_max, gr_vector_void_star(1, pmt::uniform_vector_writable_elements(vec,arg)) );
        message_port_pub(pmt::mp("pdus"), pmt::cons(p.first, vec));
    }

    std::pair<pmt::pmt_t, int> 
    source_impl::work_chunk(int maxlen, gr_vector_void_star v)
    {
        assert( maxlen >= d_min );
        float* out = (float*)v[0];
        boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
        pmt::pmt_t meta = pmt::make_dict();
        meta = pmt::dict_add(meta, pmt::mp("time"), pmt::mp(mst1.time_of_day().total_microseconds()) );
        meta = pmt::dict_add(meta, pmt::mp("seq"), pmt::mp(d_seq++) );
        int len = d_min + random()%(std::max(d_max,maxlen)-d_min);
        for(int i=0; i<len; i++){
            out[i] = (float)i+1;
            }
        return std::pair<pmt::pmt_t, int>(meta, len);
    }

  } /* namespace chunky */
} /* namespace gr */

