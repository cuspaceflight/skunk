#ifndef FLOWMETERDRIVER_H
#define FLOWMETERDRIVER_H

#include <Arduino.h>
#include "SkunkPinDefs.h"

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

void flowmeter_setup();
void flowmeter_setup_valve_control();
float flowmeter_get_accumulation();
void flowmeter_set_valve(unsigned short percentageOpen);

void flowmeter_start_flow();
void flowmeter_stop_flow();

// PRIVATE

float getFloatFromResponse(String ss);
void num_to_hex(short w, short hex_len, char data[]);

void sendMessage(short node, String data);

void sendParameterData(short processNumber, short paramType, short paramNumber, String data, char buf[], int buflen);
void requestParameterData(short processNumber, short paramType, short paramNumber, char buf[], int buflen);

void sendChar(short processNumber, short parameterNumber, char data, char buf[], int buflen);
void sendInt(short processNumber, short parameterNumber, int data, char buf[], int buflen);
void sendFloat(short processNumber, short parameterNumber, float data, char buf[], int buflen);
void requestFloat(short processNumber, short parameterNumber, char buf[], int buflen);
void sendLong(short processNumber, short parameterNumber, long data, char buf[], int buflen);
void sendString(short processNumber, short parameterNumber, String data, char buf[], int buflen);

#endif
