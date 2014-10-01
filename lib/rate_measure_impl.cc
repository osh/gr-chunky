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
#include "rate_measure_impl.h"

namespace gr {
  namespace chunky {

    rate_measure::sptr
    rate_measure::make(int itemsize)
    {
      return gnuradio::get_initial_sptr
        (new rate_measure_impl(itemsize));
    }

    rate_measure_impl::rate_measure_impl(int itemsize)
      : gr::sync_block("rate_measure",
              gr::io_signature::make(1,1, itemsize),
              gr::io_signature::make(0,0,0)),
        d_last_now(0),
        d_last_items(0)
    {}

    rate_measure_impl::~rate_measure_impl()
    {
    }


    bool
    rate_measure_impl::start()
    {
        boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
        uint64_t now( mst1.time_of_day().total_microseconds() );
        d_last_now = now;
        d_start_now = now;
        d_last_items = 0;
        printf("now,items,items_last,rate_last,rate_total\n");
    }
    
    int
    rate_measure_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        boost::posix_time::ptime mst1 = boost::posix_time::microsec_clock::local_time();
        uint64_t now( mst1.time_of_day().total_microseconds() );
        uint64_t diff_time = now - d_last_now;
        if(diff_time >= 1e6){
            uint64_t items_now = nitems_read(0);
            uint64_t diff_items = items_now - d_last_items;
            float rate_last = diff_items * 1e6 / diff_time;
            float rate_total = items_now * 1e6 / (now - d_start_now);
            printf("%lu,%lu,%lu,%f,%f\n",now,items_now,diff_items,rate_last,rate_total);
            d_last_now = now;
            d_last_items = nitems_read(0);
            }
        return noutput_items;
    }

  } /* namespace chunky */
} /* namespace gr */

