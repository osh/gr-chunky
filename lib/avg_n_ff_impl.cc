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
#include "avg_n_ff_impl.h"

namespace gr {
  namespace chunky {

    avg_n_ff::sptr
    avg_n_ff::make(int k)
    {
      return gnuradio::get_initial_sptr
        (new avg_n_ff_impl(k));
    }

    /*
     * The private constructor
     */
    avg_n_ff_impl::avg_n_ff_impl(int k)
      : gr::tagged_stream_block("avg_n_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)), "packet_len"),
        d_k(k)
    {}

    /*
     * Our virtual destructor.
     */
    avg_n_ff_impl::~avg_n_ff_impl()
    {
    }

    int
    avg_n_ff_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int shortened_avgs = ninput_items[0]%d_k==0 ? 0 : 1;
      int noutput_items = ninput_items[0]/d_k + shortened_avgs;
      return noutput_items ;
    }

    int
    avg_n_ff_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {


        std::vector<tag_t> tags;
        get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0)+1);
        for(int i=0; i<tags.size(); i++){
            add_item_tag( 0, nitems_written(0), tags[i].key, tags[i].value, pmt::PMT_NIL );
//            pmt::print( tags[i].key );
            }

        const float *in = (const float*) input_items[0];
        float *out = (float *) output_items[0];

        int shortened_avgs = ninput_items[0]%d_k==0 ? 0 : 1;
        int shortened_len = d_k - ninput_items[0]%d_k;
        int full_avgs = ninput_items[0]/d_k;
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

        // Tell runtime system how many output items we produced.
        return full_avgs + shortened_avgs;
    }

  } /* namespace chunky */
} /* namespace gr */

