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


#ifndef INCLUDED_CHUNKY_REPLICATE_H
#define INCLUDED_CHUNKY_REPLICATE_H

#include <chunky/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace chunky {

    /*!
     * \brief <+description of block+>
     * \ingroup chunky
     *
     */
    class CHUNKY_API replicate : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<replicate> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of chunky::replicate.
       *
       * To avoid accidental use of raw pointers, chunky::replicate's
       * constructor is in a private implementation
       * class. chunky::replicate::make is the public interface for
       * creating new instances.
       */
      static sptr make(int item_size, int k);
    };

  } // namespace chunky
} // namespace gr

#endif /* INCLUDED_CHUNKY_REPLICATE_H */

