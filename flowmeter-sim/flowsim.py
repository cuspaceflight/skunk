#!/usr/bin/python
'''
Flowmeter simulator for testing Skunk

Listens for serial commands from Skunk and replies with some spoofed data.

Arguments:
  portname: serial port device to listen on (e.g. /dev/ttyUSB0)
  nodenumber: which node address to present as (default: 3)
'''

import sys
from construct import *
import serial
import struct

############# GLOBAL VARS #############
VERBOSE = False

pri_node_num = 0
sec_node_num = 0
next_node_num = 0
last_node_num = 255
portname = ""
#######################################

###### UPDATES WAITING FOR RESET ######
temp_pri_node_num = -1
temp_sec_node_num = -1
temp_next_node_num = -1
temp_last_node_num = -1
#######################################

Status = Struct("Status",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(0), "ASCII")), # command
	Enum(UBInt8("status"),
		NO_ERROR=0x00,
		PROCESS_CLAIMED=0x01,
		COMMAND_ERROR=0x02,
		PROCESS_ERROR=0x03,
		PARAMETER_ERROR=0x04,
		PARAMETER_TYPE_ERROR=0x05,
		PARAMETER_VALUE_ERROR=0x06,
		NETWORK_NOT_ACTIVE=0x07,
		TIMEOUT_START_CHARACTER=0x08,
		TIMEOUT_SERIAL_LINE=0x09,
		HARDWARE_MEMORY_ERROR=0x0A,
		NODE_NUMBER_ERROR=0x0B,
		GENERAL_COMMUNICATION_ERROR=0x0C,
		READ_ONLY_PARAMETER=0x0D,
		ERROR_PC_COMUNICATION=0x0E,
		NO_RS232_CONNECTION=0x0F,
		PC_OUT_OF_MEMORY=0x10,
		WRITE_ONLY_PARAMETER=0x11,
		SYSTEM_CONFIGURATION_UNKNOWN=0x12,
		NO_FREE_NODE_ADDRESS=0x13,
		WRONG_INTERFACE_TYPE=0x14,
		ERROR_SERIAL_PORT_CONNECTION=0x15,
		ERROR_OPENING_COMMUNICATION=0x16,
		COMMUNICATION_ERROR=0x17,
		ERROR_INTERFACE_BUSMASTER=0x18,
		TIMEOUT_ANSWER=0x19,
		NO_START_CHARACTER=0x1A,
		ERROR_FIRST_DIGIT=0x1B,
		BUFFER_OVERFLOW_IN_HOST=0x1C,
		BUFFER_OVERFLOW=0x1D,
		NO_ANSWER_FOUND=0x1E,
		ERROR_CLOSING_COMMUNICATION=0x1F,
		SYNCHRONISATION_ERROR=0x20,
		SEND_ERROR=0x21,
		PROTOCOL_ERROR=0x22,
		BUFFER_OVERFLOW_IN_MODULE=0x23
	),
	UBInt8("index")
)

SendParamStatus = Struct("SendParamStatus",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(1), "ASCII")), # command
	UBInt8("process_number"),
	EmbeddedBitStruct(
		Enum(BitField("type", 3),
			CHAR = 0,
			INT = 1,
			LONG = 2,
			STRING = 3
		),
		BitField("param", 5)
	),
	Bytes("data", lambda ctx: ctx.length-4)
)

SendParamNoStatus = Struct("SendParamNoStatus",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(2), "ASCII")), # command
	UBInt8("process_number"),
	EmbeddedBitStruct(
		Enum(BitField("type", 3),
			CHAR = 0,
			INT = 1,
			LONG = 2,
			STRING = 3
		),
		BitField("param", 5)
	),
	Bytes("data", lambda ctx: ctx.length-4)
)

RequestParam = Struct("RequestParam",
	UBInt8("length"),
	UBInt8("node"),
	Magic(bytes(chr(4), "ASCII")), # command
	UBInt8("process_number_return"),
	EmbeddedBitStruct(
		Enum(BitField("type_return", 3),
			CHAR = 0,
			INT = 1,
			LONG = 2,
			STRING = 3
		),
		BitField("param_return", 5)
	),
	UBInt8("process_number"),
	EmbeddedBitStruct(
		Enum(BitField("type", 3),
			CHAR = 0,
			INT = 1,
			LONG = 2,
			STRING = 3
		),
		BitField("param", 5)
	)
)

## Read command line args
if len(sys.argv)<2:
	print("Usage: %s <portname> [--verbose]" % sys.argv[0])
	sys.exit(1)

portname = sys.argv[1]

if len(sys.argv)>2:
	print(sys.argv[2])
	if sys.argv[2] == "--verbose":
		VERBOSE = True

	
## Open serial port and report that we've started
#port = serial.Serial(portname, baudrate=38400);

print("\nFlowmeter-Sim Started.")
if VERBOSE: print("... in VERBOSE mode")
print("\nI'm listening on port %s, and responding as node number %d (%s)\n" % (portname, pri_node_num, '0x{:02x}'.format(pri_node_num)))

def send_packet(packet):
	ascii_packet = ":%s\r\n" % (''.join('{:02x}'.format(x) for x in packet))
	ascii_packet = ascii_packet.upper() # Flowmeter only uses uppercase
	if VERBOSE: print("> Sending %s" % ascii_packet)
	#port.write(bytes(ascii_packet))

def send_accumulation(req_pac, val):
	print("> Sending accumulation value %f..." % val)
	packed_float = struct.pack('>f', val)
	packet = SendParamNoStatus.build(Container(
				length = 8,
				node = req_pac.node,
				process_number = req_pac.process_number,
				type = req_pac.type,
				param = req_pac.param,
				data = packed_float
			))
	send_packet(packet)

# parses data section of packet
# returns a friendly string, and a raw representation
def read_data(dtype, dbs):
	if dtype=="CHAR":
		return chr(dbs[0]), '0x{:02x}'.format(dbs[0])
	elif dtype=="INT":
		raw = ''.join('{:02x}'.format(x) for x in dbs)
		return int(raw, 16), "[ %s ]" % ' '.join('0x{:02x}'.format(x) for x in dbs)
	elif dtype=="LONG":
		long_data = int(''.join('{:02x}'.format(x) for x in dbs), 16)
		float_data = struct.unpack('>f', dbs)[0]
		return long_data, float_data
	elif dtype=="STRING":
		length = dbs[0]
		raw = dbs[1:length+2] # grab the first 'length' bytes
		s = ''.join(chr(x) for x in raw)
		return s, "[ %s ]" % ' '.join('0x{:02x}'.format(x) for x in raw)
		
def process_send_param(pac, sendStatus=False):
	global temp_pri_node_num, temp_sec_node_num, temp_next_node_num, temp_last_node_num, pri_node_num, sec_node_num, next_node_num, last_node_num
	result = True
	if VERBOSE:
		print("  Process number: %d, Param: %d" % (pac.process_number, pac.param))
	## read the data
	data,data2 = read_data(pac.type, pac.data)
	if VERBOSE:
		if pac.type!="LONG":
			print("  Data: (%s) %s, RAW: %s" % (pac.type, data, data2))
		else:
			print("  Data: (LONG) %d or (FLOAT) %f" % (data, data2))
	## deal with packet contents
	if pac.param==10 and pac.type=="CHAR": # Control device
		if data=="I": # Initialise process
			print("->INITIALISE NODE %d PROCESS %d" % (pac.node, pac.process_number))
		elif data=="R": # Reset device
			print("->RESET MODULE")
			if temp_pri_node_num >= 0: pri_node_num = temp_pri_node_num
			if temp_sec_node_num >= 0: sec_node_num = temp_sec_node_num
			if temp_next_node_num >= 0: next_node_num = temp_next_node_num
			if temp_last_node_num >= 0: last_node_num = temp_last_node_num
	elif pac.param==1 and pac.type=="CHAR": # Set primary node address
		print("->SET PRIMARY NODE ADDRESS TO %d" % ord(data))
		temp_pri_node_num = ord(data)
	elif pac.param==2 and pac.type=="CHAR": # Set secondary node address
		print("->SET SECONDARY NODE ADDRESS TO %d" % ord(data))
		temp_sec_node_num = ord(data)
	elif pac.param==3 and pac.type=="CHAR": # Set next node address
		print("->SET NEXT NODE ADDRESS TO %d" % ord(data))
		temp_next_node_num = ord(data)
	elif pac.param==4 and pac.type=="CHAR": # Set last node address
		print("->SET LAST NODE ADDRESS TO %d" % ord(data))
		temp_last_node_num = ord(data)
	elif pac.param==5 and pac.type=="CHAR": # Set bus management
		bm = "EVERYTHING AUTO" if ord(data) == 67 else \
			"AUTO ARBITRATION" if ord(data) == 3 else \
			"ALWAYS BUSMASTER" if ord(data) == 2 else \
			"TEMPORARY" if ord(data) == 1 else "UNKNOWN"
		print("->SET BUS MANAGEMENT TO %d (%s)" % (ord(data), bm))
	else:
		result = False
	## send status if we need to
	if sendStatus:
		send_packet(Status.build(Container(length=4,node=pac.node,status='NO_ERROR',index=0)))
	return result

def process_request_param(pac):
	if VERBOSE:
		print("  Process number: %d, Param: %d" % (pac.process_number, pac.param))
	if pac.process_number==104 and pac.type=='LONG' and pac.param==1: # get accumulation
		send_accumulation(pac, 1.00)
		return True
	return False

def process(line):
	if line[0] != ":":
		print("< Got bad command: %s" % line.strip())
		return
	if VERBOSE: print("< Got %s" % line.strip())
	line = line[1:].strip() # trim starting colon and newline
	bs = bytes([int(line[i:i+2], 16) for i in range(0,len(line),2)]) # get chars in pairs and read as hex int
	length = bs[0]
	node = bs[1]
	if node!=128 and node!=pri_node_num:
		print(" Command not addressed to me (Sent to node %d, I'm node %d)" % (node, pri_node_num))
		return
	if len(bs) != length+1:
		print(" Got packet with invalid length: %s" % line)
		return
	command = bs[2]
	if command==0x00:
		pac = Status.parse(bs)
		if VERBOSE:
			print(" Got a STATUS packet:")
			print("  %s" % pac.status)
	elif command==0x01:
		pac = SendParamStatus.parse(bs)
		if VERBOSE:
			print(" Got a SEND PARAMETER packet for node %d:" % (pac.node))
		if not process_send_param(pac, True):
			print(" UNKNOWN PACKET: %s" % line)
	elif command==0x02:
		pac = SendParamNoStatus.parse(bs)
		if VERBOSE:
			print(" Got a SEND PARAMETER (NO STATUS) packet for node %d:" % (pac.node))
		if not process_send_param(pac):
			print(" UNKNOWN PACKET: %s" % line)
	elif command==0x04:
		pac = RequestParam.parse(bs)
		if VERBOSE:
			print(" Got a REQUEST PARAMETER packet for node %d:" % (pac.node))
		if not process_request_param(pac):
			print(" UNKNOWN PACKET: %s" % line)
	else:
		print("Got unknown command type %d:" % command)
		print("  %s" % line)

def main():
	#while True:
		#process(port.readline())
		#process(":0880026841AABBCCDD\r\n") # accumulator
		#process(":06800468416841\r\n")  # get accumulator
		process(":050001000A49\r\n")
		process(":050001000101\r\n")
		process(":05000100027F\r\n")
		process(":050001000302\r\n")
		process(":050001000420\r\n")
		process(":050001000502\r\n")
		process(":050001000A52\r\n")

if __name__ == "__main__":
	main()
	
