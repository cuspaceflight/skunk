#ifndef FLOWMETERDRIVER_H
#define FLOWMETERDRIVER_H

#include <Arduino.h>
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

// PUBLIC

void initialiseFlowmeter(SoftwareSerial flowmeter);
void setupValveControl(SoftwareSerial flowmeter);
float getAccumulation(SoftwareSerial flowmeter);
void setValve(SoftwareSerial flowmeter, unsigned short percentageOpen);

// PRIVATE

float getFloatFromResponse(String ss);
String num_to_hex(short w, short hex_len);

String createMessage(short node, String data);

String sendParameterData(short processNumber, short paramType, short paramNumber, String data);
String requestParameterData(short processNumber, short paramType, short paramNumber);

String sendChar(short processNumber, short parameterNumber, char data);
String sendInt(short processNumber, short parameterNumber, int data);
String sendFloat(short processNumber, short parameterNumber, float data);
String requestFloat(short processNumber, short parameterNumber);
String sendLong(short processNumber, short parameterNumber, long data);
String sendString(short processNumber, short parameterNumber, String data);

#endif
