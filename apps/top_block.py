#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Sun Mar 23 19:44:17 2014
##################################################

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import chunky
import pmt
import sip
import sys

class top_block(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Top Block")
        try:
             self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
             pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())


        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_time_raster_sink_x_0 = qtgui.time_raster_sink_f(
        	samp_rate,
        	100,
        	100,
        	([]),
        	([]),
        	"QT GUI Plot",
        	1,
        	)
        
        self.qtgui_time_raster_sink_x_0.set_update_time(0.10)
        
        labels = ["", "", "", "", "",
                  "", "", "", ""]
        colors = [0, 0, 0, 0, 0,
                  0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_raster_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_raster_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_raster_sink_x_0.set_color_map(i, colors[i])
            self.qtgui_time_raster_sink_x_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_raster_sink_x_0_win = sip.wrapinstance(self.qtgui_time_raster_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_raster_sink_x_0_win)
        self.chunky_replicate_0_0_0_0 = chunky.replicate(gr.sizeof_float, 3)
        self.chunky_replicate_0_0_0 = chunky.replicate(gr.sizeof_float, 3)
        self.chunky_replicate_0_0 = chunky.replicate(gr.sizeof_float, 5)
        self.chunky_replicate_0 = chunky.replicate(gr.sizeof_float, 2)
        self.chunky_avg_n_ff_0_0_0_0 = chunky.avg_n_ff(2)
        self.chunky_avg_n_ff_0_0_0 = chunky.avg_n_ff(7)
        self.chunky_avg_n_ff_0_0 = chunky.avg_n_ff(4)
        self.chunky_avg_n_ff_0 = chunky.avg_n_ff(3)
        self.blocks_random_pdu_0 = blocks.random_pdu(100, 1000, chr(0xFF), 2)
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, "packet_len")
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_message_strobe_0 = blocks.message_strobe(pmt.intern("TEST"), 100)
        self.blocks_char_to_float_0 = blocks.char_to_float(1, 1)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.chunky_avg_n_ff_0_0_0_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.chunky_replicate_0_0_0_0, 0), (self.chunky_avg_n_ff_0_0_0_0, 0))
        self.connect((self.chunky_avg_n_ff_0_0_0, 0), (self.chunky_replicate_0_0_0_0, 0))
        self.connect((self.chunky_avg_n_ff_0_0, 0), (self.chunky_replicate_0_0_0, 0))
        self.connect((self.chunky_replicate_0_0_0, 0), (self.chunky_avg_n_ff_0_0_0, 0))
        self.connect((self.chunky_replicate_0_0, 0), (self.chunky_avg_n_ff_0_0, 0))
        self.connect((self.chunky_avg_n_ff_0, 0), (self.chunky_replicate_0_0, 0))
        self.connect((self.chunky_replicate_0, 0), (self.chunky_avg_n_ff_0, 0))
        self.connect((self.blocks_char_to_float_0, 0), (self.chunky_replicate_0, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.blocks_char_to_float_0, 0))
        self.connect((self.chunky_avg_n_ff_0_0_0_0, 0), (self.qtgui_time_raster_sink_x_0, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.blocks_random_pdu_0, "pdus", self.blocks_pdu_to_tagged_stream_0, "pdus")
        self.msg_connect(self.blocks_message_strobe_0, "strobe", self.blocks_random_pdu_0, "generate")

# QT sink close method reimplementation
    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "top_block")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    Qt.QApplication.setGraphicsSystem(gr.prefs().get_string('qtgui','style','raster'))
    qapp = Qt.QApplication(sys.argv)
    tb = top_block()
    tb.start()
    tb.show()
    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()
    tb = None #to clean up Qt widgets

