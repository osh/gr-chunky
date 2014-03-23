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
#include "replicate_impl.h"

namespace gr {
  namespace chunky {

    replicate::sptr
    replicate::make(int item_size, int k)
    {
      return gnuradio::get_initial_sptr
        (new replicate_impl(item_size, k));
    }

    /*
     * The private constructor
     */
    replicate_impl::replicate_impl(int item_size, int k)
      : gr::tagged_stream_block("replicate",
              gr::io_signature::make(1,1, item_size),
              gr::io_signature::make(1, 1, item_size), "packet_len"),
        d_item_size(item_size),
        d_k(k)
    {}

    /*
     * Our virtual destructor.
     */
    replicate_impl::~replicate_impl()
    {
    }

    int
    replicate_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = ninput_items[0]*d_k;
      return noutput_items ;
    }

    int
    replicate_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {

        const uint8_t *in = (const uint8_t *) input_items[0];
        uint8_t *out = (uint8_t *) output_items[0];

        int onerep_bytes = d_item_size * ninput_items[0];
        for(int i=0; i<d_k; i++){
            memcpy(&out[i*onerep_bytes], &in[0], onerep_bytes);
        }

        // Tell runtime system how many output items we produced.
        return ninput_items[0]*d_k;
    }

  } /* namespace chunky */
} /* namespace gr */

