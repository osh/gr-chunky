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

#ifndef INCLUDED_CHUNKY_AVG_N_FPDU_IMPL_H
#define INCLUDED_CHUNKY_AVG_N_FPDU_IMPL_H

#include <chunky/avg_n_fpdu.h>

namespace gr {
  namespace chunky {

    class avg_n_fpdu_impl : public avg_n_fpdu
    {
     private:
      int d_k;

     public:
      avg_n_fpdu_impl(int k);
      ~avg_n_fpdu_impl();

      void handle(pmt::pmt_t msg);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace chunky
} // namespace gr

#endif /* INCLUDED_CHUNKY_AVG_N_FPDU_IMPL_H */

