#include "FlowmeterDriver.h"
#include "SkunkPinDefs.h"

/// PUBLIC

/**
   Init stuff - base commands that need to be sent to initialise the Flowmeter
   flowmeter: the Serial that is the flow meter
*/
void flowmeter_setup() {
  FLOW_SERIAL.begin(38400); // Baud rate specified in flowmeter docs

  sendMessage(0x80, "01000A49"); // Initialise process 0, node 128
  sendMessage(0x80, "01000101"); // Set primary node number to 1
  sendMessage(0x80, "0100027F"); // Set secondary node number to 127
  sendMessage(0x80, "01000302"); // Set next node number to 2
  sendMessage(0x80, "01000420"); // Set last node number to 32
  sendMessage(0x80, "01000502"); // Set bus management to ALWAYS BUSMASTER (0x02)

  
  
  // RESET
  sendMessage(0x80, "01000A52");
  delay(1000);

  // Must change setpoint controlmode
  // Process 01, parameter 04, Character
  // Set to 20 for "valve steering"
  char tmp[20];
  sendChar(0x01, 0x04, 20, tmp, sizeof(tmp));
  sendMessage(0x80, String(tmp));

  // Need to set CntrMode to counting upwards continuously
  // process 104 = 0x68
  // parameter 8, Char
  // Set to 1
  sendChar(0x68, 0x08, 1, tmp, sizeof(tmp));
  sendMessage(0x80, String(tmp));

}


void flowmeter_reset_flowcounter()
{
  char tmp[20];
  // Then reset counter to zero, i.e.
  // process 104 = 0x68
  // Parameter 1, Float
  // set to 0.0
  sendFloat(0x68, 0x01, 0.0f, tmp, sizeof(tmp));
  sendMessage(0x80, String(tmp));
	
	return;
}

float flowmeter_get_accumulation() {
  char buffer[128];

  // Wait for any outgoing commands to finish first
  FLOW_SERIAL.flush();
  delay(5);
  
  // First clear our read buffer, so we can read just the returned line.
  while (FLOW_SERIAL.read() != -1){
    delay(1);
  }

  // Send read counter command:
  // Process 104 = 0x68
  // Parameter 1, Float
  char tmp[20];
  requestFloat(0x68, 0x01, tmp, sizeof(tmp));
  sendMessage(0x80, String(tmp));

  Serial.println("> SENT");
  Serial.println(tmp);

  // Should receive :08??026841AABBCCDD\r\n
  // Where AABBCCDD are 4 bytes of float and ?? is flowmeter node number
  if (FLOW_SERIAL.readBytesUntil('\n', buffer, 128) >= 19) {
    float f = getFloatFromResponse(buffer);
    Serial.print("Got this: ");
    Serial.println(f);
    return f;
  }

  Serial.println("< GOT");
  Serial.println(buffer);

  return -13.37; // Fail!
}

void flowmeter_set_valve(unsigned short percentageOpen) {
  // Scale the open-ness from 0-100 to 0x0000-0x7D00
  unsigned long int rescale = ((long int)0x7D00 * (long int)percentageOpen) / 100;

  // Max value is 0x7D00, on error set to 0 (closed)
  rescale = rescale <= 0x7D00 ? rescale : 0x0000;

  char tmp[20];
  sendInt(0x01, 0x01, rescale, tmp, 20);
  sendMessage(0x80, String(tmp));
}

void flowmeter_start_flow(){
  flowmeter_set_valve(10); // Open valve to 10%
}

void flowmeter_stop_flow(){
  flowmeter_set_valve(0); // Close valve
}

/// PRIVATE

/**
   Gets the float stored as 4 pairs of hexadecimal characters AABBCCDD
   Swaps bytes around
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
   Converts the specified number to a set length hex string
*/
void num_to_hex(short w, short hex_len, char data[]) {
  /* This should work alternatively to code below
    static const String digits = "0123456789ABCDEF";
    String rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
      rc[i] = digits[(w>>j) & 0x0f];
    return rc;
  */

  String format = String("%0") + String(hex_len, DEC) + "X";

  snprintf(data, hex_len+1, format.c_str(), w); // have to add 1 to the length for the trailing \0
}

/**
   Creates a message for the flow meter to the specified node containing the specified data.
   Node/Port
   Data in Hexadecimal string
*/
void sendMessage(short node, String data) {

  short len = 1 + data.length() / 2; // length of data
  char node_data[3];
  char len_data[3];
  num_to_hex(node, 2, node_data);
  num_to_hex(len, 2, len_data);

  String ss;
  ss = ":" // start of message
       + String(len_data)
       + String(node_data)
       + data
       + "\r\n"; /// end of message

  FLOW_SERIAL.print(ss);
  /*
  delay(100);
  while(FLOW_SERIAL.available()>0){
    Serial.print(FLOW_SERIAL.read(), DEC);
    Serial.print(", ");
  }
  Serial.println();
  */
}

/**
   Create a send parameter string
   processNumber - the process
   parameterType - the type of parameter (char, int, float/long, string)
   parameterNumber - the parameter
   data - string data to send
*/
void sendParameterData(short processNumber, short paramType, short paramNumber, String data, char buf[], int buflen) {
  if (paramNumber > 31) {
    // ERROR, parameter_number must be 31 or less.
    buf[0] = 0;
  }

  enum flowmeter_command command = SEND_DESTINATION_CONFIRM;
  short param_data = paramType + paramNumber;

  char command_data[3];
  char process_num_data[3];
  char param_data_data[3];
  num_to_hex(command, 2, command_data);
  num_to_hex(processNumber, 2, process_num_data);
  num_to_hex(param_data, 2, param_data_data);

  String ss;
  ss = String(command_data)
       + String(process_num_data)
       + String(param_data_data)
       + data;
  ss.toCharArray(buf, buflen);
}

void requestParameterData(short processNumber, short paramType, short paramNumber, char buf[], int buflen) {
  if (paramNumber > 31) {
    // ERROR, parameter_number must be 31 or less.
    buf[0] = 0;
  }

  enum flowmeter_command command = REQUEST;
  short param_data = paramType + paramNumber;

  char command_data[3];
  char process_num_data[3];
  char param_data_data[3];
  num_to_hex(command, 2, command_data);
  num_to_hex(processNumber, 2, process_num_data);
  num_to_hex(param_data, 2, param_data_data);

  String sprocessNumber = String(process_num_data);
  String scommand = String(command_data);
  String sparam_data = String(param_data_data);
  
  String ss;
  ss = scommand
       + sprocessNumber
       + sparam_data
       + sprocessNumber
       + sparam_data;
  ss.toCharArray(buf, buflen);
}

/**
   Send a char/short value, 1 byte (2 hexes)
*/
void sendChar(short processNumber, short parameterNumber, char data, char buf[], int buflen) {
  char tmp[3];
  num_to_hex(data, 2, tmp);
  sendParameterData(processNumber, PARAMETER_CHARACTER, parameterNumber, String(tmp), buf, buflen);
}

/**
   Send an integer value, 2 bytes (4 hexes)
*/
void sendInt(short processNumber, short parameterNumber, int data, char buf[], int buflen) {
  char tmp[5];
  num_to_hex(data, 4, tmp);
  sendParameterData(processNumber, PARAMETER_INTEGER, parameterNumber, String(tmp), buf, buflen);
}

/**
   Send a float value, 4 bytes (8 hexes)
*/
void sendFloat(short processNumber, short parameterNumber, float data, char buf[], int buflen) {
  // Dangerous castings!
  char tmp[9];
  num_to_hex(*(int*)&data, 8, tmp);
  sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, String(tmp), buf, buflen);
}

void requestFloat(short processNumber, short parameterNumber, char buf[], int buflen) {
  requestParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, buf, buflen);
}

/**
   Send a long values, 4 bytes (8 hexes)
*/
void sendLong(short processNumber, short parameterNumber, long data, char buf[], int buflen) {
  char tmp[9];
  num_to_hex(data, 8, tmp);
  sendParameterData(processNumber, PARAMETER_FLOAT_OR_LONG, parameterNumber, String(tmp), buf, buflen);
}

void sendString(short processNumber, short parameterNumber, String data, char buf[], int buflen) {
  // TODO: Implement
}
