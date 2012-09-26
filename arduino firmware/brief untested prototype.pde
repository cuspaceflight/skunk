//To communicate with bronkhorst mass flow meter

//To get the accumalated value
//First send ':' 06 03 04 68 41 68 41 '\r' '\n'
//Will recieve the following in reply
//':' 08 03 02 68 41 (Four bytes with value) '\r' '\n'

//To measure
//Send ':' 06 03 04 01 21 01 20 '\r' '\n'
//Will recieve:
//':' 06 03 02 01 21 (Value as a proportion of 32000) (?? maybe not certain) '\r' '\n'

//To set
//Send ':' 06 03 01 01 21 (Value as two bytes as a fraction of 32000, i.e. 3E 80 is 16000, is 50%) '\r' '\n'
//Should recieve
//':' 04 01 00 00 05 '\r' '\n'

//Need to check whether/how should sort out the recieve

void setup() {
  //initialise serial communications at 9600 bps
  Serial1.begin(9600); //connected to meter
  Serial2.begin(9600); //connected to screen
}
float accumalation = 0; //total accumalated so far
float target = 0;  //target to fill to
int ready=0;
int incomingmessage[12] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int i;
int analogPin = 3;


//Main Body to go here
void loop() {
  accumalation = get_accumalation();
  if (accumalation>target) {
    stop_flow();
  }
}


//Functions
void stop_flow(){
  Serial1.println(":06030101210000");
}


void refresh_screen(){
  char line1[16];
  char line2[16];
  sprintf(line1, "Current: %d", accumalation);
  sprintf(line2, "Target: %d", target);
  Serial2.println(line1);
  Serial2.println(line2);
}



float get_accumalation(){
  float result;
  Serial1.println(":06030468416841");
  if (Serial1.available()>11) { //check the whole string is there
    for (i=0; i<12; i=i+1)
    {
      incomingmessage[i]=Serial1.read();
    }
    if (incomingmessage[6]<128){
      //Code to turn four byte hex into float
      union u_tag {
        byte b[4];
        float fval;
      } 
      u;
      u.b[0] = incomingmessage[6];
      u.b[1] = incomingmessage[7];
      u.b[2] = incomingmessage[8];
      u.b[3] = incomingmessage[9];

      result = u.fval;
    }
  }
  return result;
}


int get_setpoint(){
  int result;
  result = analogRead(analogPin);
  return result;
}


void set_setpoint(int setpoint){
  int setpoint_ratio;
  setpoint_ratio = setpoint*32000/1023;
  char message[16];
  sprintf(message, ":06030121%d", setpoint_ratio);
  Serial1.println(message);
}

