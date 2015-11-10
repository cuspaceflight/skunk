#!/usr/bin/python

import sys
from construct import *
import serial
import struct

'''
Flowmeter simulator for testing Skunk

Listens for serial commands from Skunk and replies with some spoofed data.

First argument on the command line is the serial port to listen on.

'''

Serial2 = Struct("Serial-2",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(2), "ASCII")), # command
	UBInt8("process_number"),
	BitStruct("type_and_param",
		Nibble("type"),
		Nibble("param")
	),
	Bytes("data", lambda ctx: ctx.length-4)
)

Serial4 = Struct("Serial-4",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(4), "ASCII")), # command
	UBInt8("process_number"),
	BitStruct("type_and_param",
		Nibble("type"),
		Nibble("param")
	),
	UBInt8("process_number"),
	BitStruct("type_and_param",
		Nibble("type"),
		Nibble("param")
	),
	allow_overwrite=True
)

if len(sys.argv)<2:
	print("Usage: %s <portname>" % sys.argv[0])
	sys.exit(1)

#port = serial.Serial(sys.argv[1], baudrate=38400);

def send_accumulation(val):
	packed_float = struct.pack('>f', val)
	packet = Serial2.build(Container(length=8,node=128,process_number=104,type_and_param=Container(type=4,param=1),data=packed_float))
	ascii_packet = ":%s\r\n" % (''.join('{:02x}'.format(x) for x in packet))
	print(ascii_packet)

def process(line):
	if line[0] != ":":
		print("Got bad command: %s" % line.strip())
		return
	line = line[1:].strip() # trim starting colon and newline
	bs = bytes([int(line[i:i+2], 16) for i in range(0,len(line),2)]) # get chars in pairs and read as hex int
	length = bs[0]
	if len(bs) != length+1:
		print("Got packet with invalid length: %s" % line)
		return
	command = bs[2]
	if command==0x02:
		cmd = Serial2.parse(bs)
	elif command==0x04:
		cmd = Serial4.parse(bs)
		if cmd.node==128 and cmd.process_number==104 and cmd.type_and_param.type==4 and cmd.type_and_param.param==1: # get accumulation
			s = send_accumulation(1.00);

def main():
	#while True:
		#process(port.readline())
		#process(":0880026841AABBCCDD\r\n") # accumulator
		process(":06800468416841\r\n")  # get accumulator

if __name__ == "__main__":
	main()
	
