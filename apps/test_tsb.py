#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Test Tsb
# Generated: Thu Sep 11 17:12:37 2014
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
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.chunky_source_0 = chunky.source(100, 200)
        self.chunky_sink_0 = chunky.sink(200)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.chunky_source_0, 0), (self.chunky_sink_0, 0))



    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = test_tsb()
    tb.start()
    raw_input('Press Enter to quit: ')
    tb.stop()
    tb.wait()
