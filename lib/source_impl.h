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

#ifndef INCLUDED_CHUNKY_SOURCE_IMPL_H
#define INCLUDED_CHUNKY_SOURCE_IMPL_H

#include <chunky/source.h>

namespace gr {
  namespace chunky {

    class source_impl : public source
    {
     private:
      int d_min, d_max;
      std::pair<pmt::pmt_t, int> work_chunk(int maxlen, gr_vector_void_star v);
      boost::thread d_thread;
      void thread_body();
      bool d_done;
      uint64_t d_seq;

     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      source_impl(int min, int max);
      ~source_impl();

      // Where all the action really happens
      int work(int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

      void handler(pmt::pmt_t msg);
      bool start();
      bool stop();
        
    };

  } // namespace chunky
} // namespace gr

#endif /* INCLUDED_CHUNKY_SOURCE_IMPL_H */

