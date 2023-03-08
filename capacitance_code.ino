#include <CapacitiveSensor.h>

byte LEFT_SEND    = 2;   // capacitance
byte LEFT_RECIEVE = 3;   // capacitance 
int  LEFT_OUT     = 4;   // to in pin of other arduino

byte RIGHT_SEND    = 6;  // capacitance 
byte RIGHT_RECIEVE = 7;  // capacitance 
int  RIGHT_OUT     = 8;  // to in pin of other arduino

int  BOTH_OUT      = 12; // to in pin of other arduino


CapacitiveSensor leftSense = CapacitiveSensor(LEFT_SEND, LEFT_RECIEVE);     // init
CapacitiveSensor rightSense = CapacitiveSensor(RIGHT_SEND, RIGHT_RECIEVE);  // init

// SETUP ============================================ SETUP
void setup()
{
  leftSense.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turn off auto calibration 
  rightSense.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off auto calibration
   
  pinMode(LEFT_OUT, OUTPUT);
  pinMode(RIGHT_OUT, OUTPUT);
  pinMode(BOTH_OUT, OUTPUT);
  
  Serial.begin(9600);
}


// LOOP =============================================== LOOP
void loop()
{
  long leftVal  = leftSense.capacitiveSensor(2);  // samples x2 from left cap
  long rightVal = rightSense.capacitiveSensor(2); // ditto for right

  /*Serial.print("\n\nleftVal:");  // for testing
  Serial.print(leftVal);
  
  Serial.print("\nrightVal:");
  Serial.print(rightVal);*/

  if(leftVal > 100 && rightVal > 100)
  { 
    digitalWrite(LEFT_OUT, LOW);
    digitalWrite(RIGHT_OUT, LOW);
    digitalWrite(BOTH_OUT, HIGH); 
    Serial.print("\nBOTH");
  }
  else if(leftVal > 100)
  {
    digitalWrite(LEFT_OUT, HIGH);
    digitalWrite(RIGHT_OUT, LOW);
    digitalWrite(BOTH_OUT, LOW); // cause it used to be up
    Serial.print("\nLEFT");    
  }
  else if(rightVal > 100)
  {
    digitalWrite(LEFT_OUT, LOW);
    digitalWrite(RIGHT_OUT, HIGH);
    digitalWrite(BOTH_OUT, LOW);
    Serial.print("\nRIGHT");
  }
  else   
  {
    Serial.print("\n-");
  }
}