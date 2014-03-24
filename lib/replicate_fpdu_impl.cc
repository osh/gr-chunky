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
#include "replicate_fpdu_impl.h"

namespace gr {
  namespace chunky {

    replicate_fpdu::sptr
    replicate_fpdu::make(int k)
    {
      return gnuradio::get_initial_sptr
        (new replicate_fpdu_impl(k));
    }

    replicate_fpdu_impl::replicate_fpdu_impl(int k)
      : gr::block("replicate_fpdu",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_k(k)
    {
        message_port_register_in(pmt::mp("fpdus"));
        message_port_register_out(pmt::mp("fpdus"));
        set_msg_handler(pmt::mp("fpdus"), boost::bind(&replicate_fpdu_impl::handle, this, _1));
    }

    void
    replicate_fpdu_impl::handle(pmt::pmt_t msg)
    {
        pmt::pmt_t meta = pmt::car(msg);
        pmt::pmt_t ivec = pmt::cdr(msg);
        size_t ilen = pmt::length(ivec);
        size_t olen = ilen*d_k;
        pmt::pmt_t ovec = pmt::make_f32vector(olen, 0);
        const float* in  = pmt::f32vector_elements(ivec, ilen);
        float* out = pmt::f32vector_writable_elements(ovec, olen);
       
        // common code
        int onerep_elements = ilen;
        for(int i=0; i<d_k; i++){
            memcpy(&out[i*onerep_elements], &in[0], onerep_elements*sizeof(float));
        }
        // common code

        message_port_pub(pmt::mp("fpdus"), pmt::cons(meta, ovec));
    }

    int
    replicate_fpdu_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        throw std::runtime_error("not a stream block");
    }

  } /* namespace chunky */
} /* namespace gr */

