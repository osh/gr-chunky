/* -*- c++ -*- */

#define CHUNKY_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "chunky_swig_doc.i"

%{
#include "chunky/replicate.h"
#include "chunky/avg_n_ff.h"
#include "chunky/replicate_fpdu.h"
#include "chunky/avg_n_fpdu.h"
#include "chunky/source.h"
%}

%include "chunky/replicate.h"
GR_SWIG_BLOCK_MAGIC2(chunky, replicate);
%include "chunky/avg_n_ff.h"
GR_SWIG_BLOCK_MAGIC2(chunky, avg_n_ff);
%include "chunky/replicate_fpdu.h"
GR_SWIG_BLOCK_MAGIC2(chunky, replicate_fpdu);
%include "chunky/avg_n_fpdu.h"
GR_SWIG_BLOCK_MAGIC2(chunky, avg_n_fpdu);
%include "chunky/source.h"
GR_SWIG_BLOCK_MAGIC2(chunky, source);
