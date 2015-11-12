from construct import *

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
