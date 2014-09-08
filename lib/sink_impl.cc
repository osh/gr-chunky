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
    sink::make()
    {
      return gnuradio::get_initial_sptr
        (new sink_impl());
    }

    sink_impl::sink_impl()
      : gr::tagged_stream_block("sink",
              gr::io_signature::make(0,1, sizeof(float)),
              gr::io_signature::make(0,0,0), "packet_len")
    {}

    sink_impl::~sink_impl()
    {
    }

    int
    sink_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = 200;
      return noutput_items ;
    }

    int
    sink_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        printf("noutput_items = %d\n", noutput_items);
        return noutput_items;
    }

  } /* namespace chunky */
} /* namespace gr */

