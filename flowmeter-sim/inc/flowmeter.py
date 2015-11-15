from debug import debug_print
from packets import *
from processes import *

class FlowMeter:
	def __init__(self, port):
		self.port = port
		self.pri_node_num = 0
		self.sec_node_num = 0
		self.next_node_num = 0
		self.last_node_num = 255
		self.accumulation = 0.0
		## these numbers taken from the Flowmeter-RS232 spec document
		self.processes = {
				0: ConfigurationProcess(self),
				1: ControlProcess(self),
				104: CounterProcess(self),
			}
	
	def send_packet(self, packet):
		ascii_packet = ":%s\r\n" % (''.join('{:02x}'.format(x) for x in packet))
		ascii_packet = ascii_packet.upper() # Flowmeter only uses uppercase
		debug_print("> Sending %s" % ascii_packet)
		self.port.write(bytes(ascii_packet, "ASCII"))
	
	## parses data section of packet
	## returns a friendly string, and a raw representation
	def read_data(self, dtype, dbs):
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
	
	def process(self, line):
		if line[0] != ":":
			print("< Got bad command: %s" % line.strip())
			return
		debug_print("< Got %s" % line.strip())
		line = line[1:].strip() # trim starting colon and newline
		bs = bytes([int(line[i:i+2], 16) for i in range(0,len(line),2)]) # get chars in pairs and read as hex int
		length = bs[0]
		if len(bs) != length+1:
			print(" Got packet with invalid length: %s" % line)
			return
		node = bs[1]
		if node!=128 and node!=self.pri_node_num:
			print(" Command not addressed to me (Sent to node %d, I'm node %d)" % (node, self.pri_node_num))
			return
		command = bs[2]
		if command==0x00:
			pac = Status.parse(bs)
			debug_print(" Got a STATUS packet:")
			debug_print("  %s" % pac.status)
		elif command==0x01:
			pac = SendParamStatus.parse(bs)
			debug_print(" Got a SEND PARAMETER packet for node %d:" % (pac.node))
			if not self.processes[pac.process_number].send_param(pac, True):
				print(" UNKNOWN PACKET: %s" % line)
		elif command==0x02:
			pac = SendParamNoStatus.parse(bs)
			debug_print(" Got a SEND PARAMETER (NO STATUS) packet for node %d:" % (pac.node))
			if not self.processes[pac.process_number].send_param(pac):
				print(" UNKNOWN PACKET: %s" % line)
		elif command==0x04:
			pac = RequestParam.parse(bs)
			debug_print(" Got a REQUEST PARAMETER packet for node %d:" % (pac.node))
			if not self.processes[pac.process_number].req_param(pac):
				print(" UNKNOWN PACKET: %s" % line)
		else:
			print("Got unknown command type %d:" % command)
			print("  %s" % line)

