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

#ifndef INCLUDED_CHUNKY_SINK_IMPL_H
#define INCLUDED_CHUNKY_SINK_IMPL_H

#include <chunky/sink.h>

namespace gr {
  namespace chunky {

    class sink_impl : public sink
    {
     private:
      void work_chunk(pmt::pmt_t meta, gr_vector_int ninput_items, gr_vector_const_void_star input_items);
      void handler(pmt::pmt_t msg);
      uint64_t d_nitems;
      uint64_t d_npkts;
      uint64_t d_ts;
      int d_exitafter;
    
     public:
      sink_impl(int maxlen, int exitafter);
      ~sink_impl();

      // Where all the action really happens
      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace chunky
} // namespace gr

#endif /* INCLUDED_CHUNKY_SINK_IMPL_H */

