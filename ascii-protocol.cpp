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

#include <iomanip>

enum flowmeter_command {
    STATUS                   = 0x00,
    SEND_DESTINATION_CONFIRM = 0x01,
    SEND_DESTINATION         = 0x02,
    SEND_SOURCE              = 0x03,
    REQUEST                  = 0x04,
    REPEAT                   = 0x05,
    STOP_PROCESS             = 0x06,
    START_PROCESS            = 0x07,
    CLAIM_PROCESS            = 0x08,
    UNCLAIM_PROCESS          = 0x09
}

enum parameter_type {
    CHARACTER     = 0x00,
    INTEGER       = 0x20,
    FLOAT_OR_LONG = 0x40,
    STRING        = 0x60
}

/**
 * Converts the specified short to a set length hex string
 */
std::string int_to_hex(int i, short width) {
    // std::stringstream stream;
//     stream << std::setfill('0') // fill with zero
//            << std::setw(width)  // hard coded to width of 2
//            << std::hex << i;
    
    // rewrite?
    
    return stream.str();
}

/**
 * Creates a message for the flow meter to the specified node containing the specified data.
 * Node/Port
 * Data in Hexadecimal string
 */
std::string createMessage(short node, std::string data) {
    
    short length = 1 + strlen(data) / 2; // length of data
    
    stringstream ss;
    ss << ':' // start of message
       << int_to_hex(length, 2) << int_to_hex(node, 2) << data 
       << "\r\n"; /// end of message
    
    return ss.str();
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
std::string sendParameterData(
    short processNumber,
    parameter_type parameterType,
    short parameterNumber,
    std::string data
) {
    if (parameter_number > 31) {
        // ERROR, parameter_number must be 31 or less.
        return "";
    }
    
    flowmeter_command command = SEND_DESTINATION_CONFIRM;
    short parameter_data = parameterType + parameterNumber;
    
    std::stringstream stream;
    stream << int_to_hex(command, 2)
           << int_to_hex(processNumber, 2)
           << int_to_hex(parameter_data, 2)
           << data;
    return stream.str();
}

std::string sendChar(short processNumber, short parameterNumber, char data) {
    std::string dataString = int_to_hex(data, 2);
    
    return sendParameterData(processNumber, CHARACTER, parameterNumber, dataString);
}

/**
 * Send an integer value
 */
std::string sendInt(short processNumber, short parameterNumber, int data) {
    std::string dataString = int_to_hex(data, 4);
    
    return sendParameterData(processNumber, INTEGER, parameterNumber, dataString);
}

std::string sendFloat(short processNumber, short parameterNumber, float data) {
    // Dangerous stuff
    int* q = (int*)&data;
    std::string dataString = int_to_hex(q, 4);
    
    return sendParameterData(processNumber, FLOAT_OR_LONG, parameterNumber, dataString);
}

std::string sendLong(short processNumber, short parameterNumber, long data) {
    std::string dataString = int_to_hex(data, 4);
    
    return sendParameterData(processNumber, FLOAT_OR_LONG, parameterNumber, dataString);
}

std::string sendString(short processNumber, short parameterNumber, std::string data) {
    // TODO: Implement
}
