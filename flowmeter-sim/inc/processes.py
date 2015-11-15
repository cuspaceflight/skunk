from debug import debug_print
from packets import *
import struct

class Process:
	def __init__(self, meter):
		self.meter = meter
	
	def send_param(self, pac, sendStatus=False):
		debug_print("  Process number: %d, Param: %d" % (pac.process_number, pac.param))
		return False
	
	def req_param(self, pac):
		debug_print("  Process number: %d, Param: %d" % (pac.process_number, pac.param))
		return False

class ConfigurationProcess(Process):
	def __init__(self, meter):
		Process.__init__(self, meter)
		
	def send_param(self, pac, sendStatus=False):
		Process.send_param(self, pac, sendStatus)
		result = True
		## read the data
		data,data2 = self.meter.read_data(pac.type, pac.data)
		if pac.type!="LONG":
			debug_print("  Data: (%s) %s, RAW: %s" % (pac.type, data, data2))
		else:
			debug_print("  Data: (LONG) %d or (FLOAT) %f" % (data, data2))
		## deal with packet contents
		if pac.param==10 and pac.type=="CHAR": # Control device
			if data=="I": # Initialise process
				print("->INITIALISE NODE %d PROCESS %d" % (pac.node, pac.process_number))
			elif data=="R": # Reset device
				print("->RESET MODULE")
				if self.temp_pri_node_num >= 0: self.meter.pri_node_num = self.temp_pri_node_num
				if self.temp_sec_node_num >= 0: self.meter.sec_node_num = self.temp_sec_node_num
				if self.temp_next_node_num >= 0: self.meter.next_node_num = self.temp_next_node_num
				if self.temp_last_node_num >= 0: self.meter.last_node_num = self.temp_last_node_num
		elif pac.param==1 and pac.type=="CHAR": # Set primary node address
			print("->SET PRIMARY NODE ADDRESS TO %d" % ord(data))
			self.temp_pri_node_num = ord(data)
		elif pac.param==2 and pac.type=="CHAR": # Set secondary node address
			print("->SET SECONDARY NODE ADDRESS TO %d" % ord(data))
			self.temp_sec_node_num = ord(data)
		elif pac.param==3 and pac.type=="CHAR": # Set next node address
			print("->SET NEXT NODE ADDRESS TO %d" % ord(data))
			self.temp_next_node_num = ord(data)
		elif pac.param==4 and pac.type=="CHAR": # Set last node address
			print("->SET LAST NODE ADDRESS TO %d" % ord(data))
			self.temp_last_node_num = ord(data)
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
			self.meter.send_packet(Status.build(Container(length=4,node=pac.node,status='NO_ERROR',index=0)))
		return result

class ControlProcess(Process):
	def __init__(self, meter):
		Process.__init__(self, meter)
	
	def send_param(self, pac, sendStatus=False):
		Process.send_param(self, pac, sendStatus)
		result = True
		## read the data
		data,data2 = self.meter.read_data(pac.type, pac.data)
		if pac.type!="LONG":
			debug_print("  Data: (%s) %s, RAW: %s" % (pac.type, data, data2))
		else:
			debug_print("  Data: (LONG) %d or (FLOAT) %f" % (data, data2))
		## deal with packet contents
		if pac.param==1 and pac.type=="INT": # Setpoint (valve control)
			print("->SET VALVE TO %d / 32000 (%d%%)" % (data, (data/32000.0)*100))
		else:
			result = False
		## send status if we need to
		if sendStatus:
			self.meter.send_packet(Status.build(Container(length=4,node=pac.node,status='NO_ERROR',index=0)))
		return result

class CounterProcess(Process):
	def __init__(self, meter):
		Process.__init__(self, meter)
	
	def send_accumulation(self, req_pac, val):
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
		self.meter.send_packet(packet)
		self.meter.accumulation += 0.51
	
	def req_param(self, pac):
		Process.req_param(self, pac)
		if pac.param==1 and pac.type=='LONG': # get accumulation
			self.send_accumulation(pac, self.meter.accumulation)
			return True
		return False
