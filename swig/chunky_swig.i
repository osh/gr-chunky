/* -*- c++ -*- */

#define CHUNKY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "chunky_swig_doc.i"

%{
#include "chunky/replicate.h"
#include "chunky/avg_n_ff.h"
%}

%include "chunky/replicate.h"
GR_SWIG_BLOCK_MAGIC2(chunky, replicate);
%include "chunky/avg_n_ff.h"
GR_SWIG_BLOCK_MAGIC2(chunky, avg_n_ff);
