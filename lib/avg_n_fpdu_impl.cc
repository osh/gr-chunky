/* -*- c++ -*- */
/* 
 * Copyright 2014 Tim O'Shea.
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
#include "avg_n_fpdu_impl.h"

namespace gr {
  namespace chunky {

    avg_n_fpdu::sptr
    avg_n_fpdu::make(int k)
    {
      return gnuradio::get_initial_sptr
        (new avg_n_fpdu_impl(k));
    }

    /*
     * The private constructor
     */
    avg_n_fpdu_impl::avg_n_fpdu_impl(int k)
      : gr::block("avg_n_fpdu",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_k(k)
    {
        message_port_register_in(pmt::mp("fpdus"));
        message_port_register_out(pmt::mp("fpdus"));
        set_msg_handler(pmt::mp("fpdus"), boost::bind(&avg_n_fpdu_impl::handle, this, _1));
    }

    void
    avg_n_fpdu_impl::handle(pmt::pmt_t msg){
        pmt::pmt_t meta = pmt::car(msg);
        pmt::pmt_t ivec = pmt::cdr(msg);
        size_t ilen = pmt::length(ivec);
        int shortened_avgs = ilen%d_k==0 ? 0 : 1;
        int shortened_len = d_k - ilen%d_k;
        int full_avgs = ilen/d_k;
        size_t olen = (full_avgs + shortened_avgs);
        pmt::pmt_t ovec = pmt::make_f32vector(olen, 0);
        const float* in  = pmt::f32vector_elements(ivec, ilen);
        float* out = pmt::f32vector_writable_elements(ovec, olen);

        // common code
        for(int i=0; i<full_avgs; i++){
            float avg = 0;
            for(int j=0; j<d_k; j++){
                avg += in[i*d_k + j];
                }
            out[i] = avg / d_k;
            }
        if(shortened_avgs > 0){
            float avg = 0;
            for(int j=0; j<shortened_len; j++){
                avg += in[full_avgs*d_k + j];
            }
            out[full_avgs] = avg/shortened_len;
        }
        // common code

        message_port_pub(pmt::mp("fpdus"), pmt::cons(meta, ovec));
    }

    /*
     * Our virtual destructor.
     */
    avg_n_fpdu_impl::~avg_n_fpdu_impl()
    {
    }

    int
    avg_n_fpdu_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        throw std::runtime_error("not a strema block");
    }

  } /* namespace chunky */
} /* namespace gr */

