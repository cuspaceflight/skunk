#!/usr/bin/python
'''
Hideously over-engineered Flowmeter simulator for testing Skunk

Listens for serial commands from Skunk and replies with some spoofed data.

Arguments:
  portname: serial port device to listen on (e.g. /dev/ttyUSB0)
  --verbose: prints out extra debug information
'''

import sys
from construct import *
import serial
import struct
import time

sys.path.insert(0, "./inc")

from packets import *
import flowmeter
import debug

############# GLOBAL VARS #############
portname = ""
#######################################

## Read command line args
if len(sys.argv)<2:
	print("Usage: %s <portname> [--verbose]" % sys.argv[0])
	sys.exit(1)

portname = sys.argv[1]

if len(sys.argv)>2:
	if sys.argv[2] == "--verbose":
		debug.VERBOSE = True

	
## Open serial port and report that we've started
port = serial.Serial(portname, baudrate=38400)
meter = flowmeter.FlowMeter(port)

print("\nFlowmeter-Sim Started.")
debug.debug_print("... in VERBOSE mode")
print("\nI'm listening on port %s, and responding as node number %d (%s)\n" % (portname, meter.pri_node_num, '0x{:02x}'.format(meter.pri_node_num)))

def main():
	while True:
		line = port.readline()
		print(line)
		meter.process(line.decode("ascii"))
		time.sleep(0.1)
		#meter.process(":0880026841AABBCCDD\r\n") # accumulator
		#meter.process(":06800468416841\r\n")  # get accumulator
		#meter.process(":050001000A49\r\n")
		#meter.process(":050001000101\r\n")
		#meter.process(":05000100027F\r\n")
		#meter.process(":050001000302\r\n")
		#meter.process(":050001000420\r\n")
		#meter.process(":050001000502\r\n")
		#meter.process(":050001000A52\r\n")
		#meter.process(":06800101210C80\r\n")
		#meter.process(":06800101210000\r\n")
		#meter.process(":06800101217D00\r\n")

if __name__ == "__main__":
	main()
	
