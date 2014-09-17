#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Test Tsb
# Generated: Wed Sep 17 11:04:58 2014
##################################################

from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import chunky

class test_tsb(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Test Tsb")

        ##################################################
        # Blocks
        ##################################################
        self.chunky_source_0 = chunky.source(100, 200)
        self.chunky_sink_0 = chunky.sink(200)
        self.chunky_avg_n_ff_0 = chunky.avg_n_ff(3)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.chunky_source_0, 0), (self.chunky_avg_n_ff_0, 0))
        self.connect((self.chunky_avg_n_ff_0, 0), (self.chunky_sink_0, 0))



if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = test_tsb()
    tb.start()
    raw_input('Press Enter to quit: ')
    tb.stop()
    tb.wait()
