#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Test Pdu
# Generated: Fri Sep 12 05:59:01 2014
##################################################

from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import chunky

class test_pdu(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Test Pdu")

        ##################################################
        # Blocks
        ##################################################
        self.chunky_source_0 = chunky.source(100, 200)
        self.chunky_sink_0 = chunky.sink(200)
        self.chunky_avg_n_fpdu_0 = chunky.avg_n_fpdu(3)

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.chunky_source_0, "pdus", self.chunky_avg_n_fpdu_0, "fpdus")
        self.msg_connect(self.chunky_avg_n_fpdu_0, "fpdus", self.chunky_sink_0, "pdus")


if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = test_pdu()
    tb.start()
    raw_input('Press Enter to quit: ')
    tb.stop()
    tb.wait()
