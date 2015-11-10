// Explanation of the messages to the Flow meter. 
//
// ASCII protocol of communication
// 
// Start of message: ":"
// End of message: CR as in "\r\n"
// Length in 2 hex numbers, e.g. "0A" for 10

// EXAMPLE
// start up: : 05 00 01 00 0A 49 \r\n
// length: 5 (1 for node, 5 for data)
// node: 00
// data: 01 00 0A 49

#include <SoftwareSerial.h>

enum flowmeter_command {
    STATUS                   = 0x00,
    SEND_DESTINATION_CONFIRM = 0x01,
    SEND_DESTINATION         = 0x02,
    SEND_SOURCE              = 0x03,
    REQUEST                  = 0x04,
    REPEAT_PROCESS           = 0x05,
    STOP_PROCESS             = 0x06,
    START_PROCESS            = 0x07,
    CLAIM_PROCESS            = 0x08,
    UNCLAIM_PROCESS          = 0x09
};

const short PARAMETER_CHARACTER     = 0x00;
const short PARAMETER_INTEGER       = 0x20;
const short PARAMETER_FLOAT_OR_LONG = 0x40;
const short PARAMETER_STRING        = 0x60;

// Declare things
String num_to_hex(short w, short hex_len);
String createMessage(short node, String data);
void initialiseFlowmeter(SoftwareSerial flowmeter);
String sendParameterData(short processNumber, short parameterType, short parameterNumber, String data);
String sendChar(short processNumber, short parameterNumber, char data);
String sendInt(short processNumber, short parameterNumber, int data);
String sendFloat(short processNumber, short parameterNumber, float data);
String sendLong(short processNumber, short parameterNumber, long data);
String sendString(short processNumber, short parameterNumber, String data);

/**
 * Converts the specified number to a set length hex string
 */
String num_to_hex(short w, short hex_len) {
    static const String digits = "0123456789ABCDEF";
    String rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

/**
 * Creates a message for the flow meter to the specified node containing the specified data.
 * Node/Port
 * Data in Hexadecimal string
 */
String createMessage(short node, String data) {
    
    short length = 1 + data.length() / 2; // length of data
    
    String ss;
    ss = ":" // start of message
       + num_to_hex(length, 2)
       + num_to_hex(node, 2)
       + data
       + "\r\n"; /// end of message
    
    return ss;
}

/**
 * Init stuff - base commands that need to be sent to initialise the Flowmeter
 * flowmeter: the Serial that is the flow meter
 */
void initialiseFlowmeter(SoftwareSerial flowmeter) {
    flowmeter.print(createMessage(0, "01000A49"));
    flowmeter.print(createMessage(0, "01000101"));
    flowmeter.print(createMessage(0, "0100027F"));
    flowmeter.print(createMessage(0, "01000302"));
    flowmeter.print(createMessage(0, "01000420"));
    flowmeter.print(createMessage(0, "01000502"));
    
    // RESET
    flowmeter.print(createMessage(0, "01000A52"));
    delay(1000);
}

/**
 * Create a send parameter string
 * processNumber - the process
 * parameterType - the type of parameter (char, int, float/long, string)
 * parameterNumber - the parameter
 * data - string data to send
 */
String sendParameterData(
    short processNumber,
    short parameterType,
    short parameterNumber,
    String data
) {
    if (parameterNumber > 31) {
        // ERROR, parameter_number must be 31 or less.
        return "";
    }
    
    enum flowmeter_command command = SEND_DESTINATION_CONFIRM;
    short parameter_data = parameterType + parameterNumber;
    
    String ss;
    ss = num_to_hex(command, 2)
       + num_to_hex(processNumber, 2)
       + num_to_hex(parameter_data, 2)
       + data;
    return ss;
}

String sendChar(short processNumber, short parameterNumber, char data) {
    String dataString = num_to_hex(data, 2);
    
    return sendParameterData(processNumber, PARAMETER_CHARACTER, parameterNumber, dataString);
}

/**
 * Send an integer value
 */
String sendInt(short processNumber, short parameterNumber, int data) {
    String dataString = num_to_hex(data, 4);
    
    return sendParameterData(processNumber, PARAMETER_INTEGER, parameterNumber, dataString);
}

String sendFloat(short processNumber, short parameterNumber, float data) {
    // Dangerous stuff
    short* q = (short*)&data;
    String dataString = num_to_hex(*q, 4);
    
    return sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, dataString);
}

String sendLong(short processNumber, short parameterNumber, long data) {
    String dataString = num_to_hex(data, 4);
    
    return sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, dataString);
}

String sendString(short processNumber, short parameterNumber, String data) {
    // TODO: Implement
}
