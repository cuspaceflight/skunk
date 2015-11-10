#include "FlowmeterDriver.h"

/// PUBLIC

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

void setupValveControl(SoftwareSerial flowmeter) {
    // Must change setpoint controlmode
    // Process 01, parameter 04, Character
    // Set to 20 for "valve steering"
    String valveSteering = sendChar(0x01, 0x04, 20);
    flowmeter.print(createMessage(0x80, valveSteering));

    // Need to set CntrMode to counting upwards continuously
    // process 104 = 0x68
    // parameter 8, Char
    // Set to 1
    String ctrlMode = sendChar(0x68, 0x08, 1);
    flowmeter.print(createMessage(0x80, ctrlMode));
    
    // Then reset counter to zero, i.e.
    // process 104 = 0x68
    // Parameter 1, Float
    // set to 0.0
    String resetCounter = sendFloat(0x68, 0x01, 0.0f);
    flowmeter.print(createMessage(0x80, resetCounter));
}

float getAccumulation(SoftwareSerial flowmeter) {
    char buffer[128];

    // First clear our read buffer, so we can read just the returned line.
    while(flowmeter.read() != -1);

    // Send read counter command:       
    // Process 104 = 0x68
    // Parameter 1, Float
    String readCounter = requestFloat(0x68, 0x01);
    flowmeter.print(createMessage(0x80, readCounter));
  
    // Should receive :08??026841AABBCCDD\r\n
    // Where AABBCCDD are 4 bytes of float and ?? is flowmeter node number
    if(flowmeter.readBytesUntil('\n', buffer, 128) >= 19) {
        return getFloatFromResponse(buffer);
    }

    return -13.37; // Fail!
}

void setValve(SoftwareSerial flowmeter, unsigned short percentageOpen) {
    // Scale the open-ness from 0-100 to 0x0000-0x7D00
    unsigned short rescale = 0x7D00 * percentageOpen / 100;

    // Max value is 0x7D00, on error set to 0 (closed)
    rescale = rescale > 0x7D00 ? rescale : 0x0000;

    String valve = sendInt(0x01, 0x01, rescale);
    flowmeter.print(createMessage(0x80, valve));
}

/// PRIVATE

/**
 * Gets the float stored as 4 pairs of hexadecimal characters AABBCCDD
 * Swaps bytes around
 */
float getFloatFromResponse(String ss) {
    char onebyte[3];
    byte bytes[4];
    
    onebyte[2] = '\0';

    // last byte - AA
    onebyte[0] = ss[11];
    onebyte[1] = ss[12];
    bytes[3] = byte(strtoul(onebyte, NULL, 16));
    
    // third byte - BB
    onebyte[0] = ss[13];
    onebyte[1] = ss[14];
    bytes[2] = byte(strtoul(onebyte, NULL, 16));
    
    // second byte -- CC
    onebyte[0] = ss[15];
    onebyte[1] = ss[16];
    bytes[1] = byte(strtoul(onebyte, NULL, 16));
    
    // first byte -- DD
    onebyte[0] = ss[17];
    onebyte[1] = ss[18];
    bytes[0] = byte(strtoul(onebyte, NULL, 16));

    return *(float*)&bytes;
}

/**
 * Converts the specified number to a set length hex string
 */
String num_to_hex(short w, short hex_len) {
    /* This should work alternatively to code below
    static const String digits = "0123456789ABCDEF";
    String rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
    */
    
    char data[hex_len];
    
    String format = String("%0") + hex_len + "X";

    snprintf(data, hex_len, format.c_str(), w);
    
    return data;
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
 * Create a send parameter string
 * processNumber - the process
 * parameterType - the type of parameter (char, int, float/long, string)
 * parameterNumber - the parameter
 * data - string data to send
 */
String sendParameterData(short processNumber, short paramType, short paramNumber, String data) {
    if (paramNumber > 31) {
        // ERROR, parameter_number must be 31 or less.
        return "";
    }

    enum flowmeter_command command = SEND_DESTINATION_CONFIRM;
    short param_data = paramType + paramNumber;
    
    String ss;
    ss = num_to_hex(command, 2)
       + num_to_hex(processNumber, 2)
       + num_to_hex(param_data, 2)
       + data;
    return ss;
}

String requestParameterData(short processNumber, short paramType, short paramNumber) {
    if (paramNumber > 31) {
        // ERROR, parameter_number must be 31 or less.
        return "";
    }
    
    enum flowmeter_command command = REQUEST;
    short param_data = paramType + paramNumber;
    
    String ss;
    ss = num_to_hex(command, 2)
       + num_to_hex(processNumber, 2)
       + num_to_hex(param_data, 2)
       + num_to_hex(processNumber, 2)
       + num_to_hex(param_data, 2);
    return ss;
}

/**
 * Send a char/short value, 1 byte (2 hexes)
 */
String sendChar(short processNumber, short parameterNumber, char data) {
    return sendParameterData(processNumber, PARAMETER_CHARACTER, parameterNumber, num_to_hex(data, 2));
}

/**
 * Send an integer value, 2 bytes (4 hexes)
 */
String sendInt(short processNumber, short parameterNumber, int data) {
    return sendParameterData(processNumber, PARAMETER_INTEGER, parameterNumber, num_to_hex(data, 4));
}

/**
 * Send a float value, 4 bytes (8 hexes)
 */
String sendFloat(short processNumber, short parameterNumber, float data) {
    // Dangerous castings!
    return sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, num_to_hex(*(int*)&data, 8));
}

String requestFloat(short processNumber, short parameterNumber) {
    return requestParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber);
}

/**
 * Send a long values, 4 bytes (8 hexes)
 */
String sendLong(short processNumber, short parameterNumber, long data) {
    return sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, num_to_hex(data, 8));
}

String sendString(short processNumber, short parameterNumber, String data) {
    // TODO: Implement
}
