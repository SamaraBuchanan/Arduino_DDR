// FROM "pitches.h":
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// PIN MAPPING ======================================= PIN MAPPING
// ROWS - all digital
const int r1 = 2;
const int r2 = 3;
const int r3 = 4;
const int r4 = 5;
const int r5 = 6;
const int r6 = 7;
const int r7 = 8;
const int r8 = 9;

// COLS - all analog 
const int a = A0;
const int b = A1;
const int c = A2;
const int d = A3;
const int e = A4;
const int f = A5;

// INPUT PINS
const int  UP   = 10;         // 0 in the input array  
const int LEFT  = 11;         // 2 
const int RIGHT = 12;         // 3 

// State booleans for Leddy's poses
// Set DOWN to true to have him hold his hands down at the start of the game
bool UP_pushed = false;
bool DOWN_pushed = true;
bool RIGHT_pushed = false;
bool LEFT_pushed = false;

const int ROW[] = {r1, r2, r3, r4, r5, r6, r7, r8}; // DIGITAL
const int COL[] = {a, b, c, d, e, f}; // ANALOG 

// MISC GAME VARS ==================================== MISC GAME VARS
// TODO randomize the patterns (STRETCH GOAL: or fit to music?) 
const int pattern1[] = {0, 1, 2, 3};
const int pattern2[] = {2, 3, 2, 3, 2, 3, 2, 2, 2, 3, 3, 3};

const char symbols[] = {'^', 'v', '<', '>'};
int symbolIndex = 0; 
long timeCount = 0; 
int patternIt = 0;
int inputs[] = {0, 0, 0, 0};
int score = 0; 
bool resolvedCorrect = false;   // 1 if resovled CORRECT button press
bool resolvedIncorrect = false; // 1 if resolved INCORRECT button press

// TODO make the rate speed up over time - maybe do rounds?
const long TIME_INTERVAL = 9000;  


// MUSIC/AUDIO ====================================== MUSIC/AUDIO
const int PIEZO_BUZZER = 13; 

// notes in the welcomeMelody:
int welcomeMelody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int welcomeNoteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

int errorSound[] = {NOTE_B0, NOTE_F1, NOTE_B0};
int errorNoteDurations[] = {8,4};

int correctSound[] = {NOTE_F4, NOTE_C4, NOTE_CS4, NOTE_A4, NOTE_AS4, NOTE_DS4};
int correctNoteDurations[] = {16,16,16,16,16,16};


// SPRITE FUNCTIONS ======================================== SPRITE FUNCTIONS

// Display Leddy with his arms up
void armsUp()
{
  // Default value on startup for LED Matrix is low, so set all columns to high
  for (int i = 0; i < 6; i++)
  {
    analogWrite(COL[i], 255); // col i  - ANALOG
  }

  // Turn desired rows high and columns low
  // Immediately reverse the operations in order to "scan" the LED
  // display and create the illusion of a stationary image
  digitalWrite(ROW[3], HIGH);   // row 4 
  digitalWrite(COL[3], 0);      // head
  digitalWrite(COL[1], 0);      // left hand  
  digitalWrite(COL[1], 255);    // left hand
  digitalWrite(COL[5], 0);      // right hand
  digitalWrite(COL[5], 255);    // right hand
  digitalWrite(ROW[3], LOW);    // head
  digitalWrite(ROW[4], HIGH);   // neck 
  digitalWrite(COL[2], 0);      // left shoulder
  digitalWrite(COL[4], 0);      // right shoulder
  digitalWrite(COL[2], 255);    // left shoulder
  digitalWrite(COL[4], 255);    // right shoulder
  digitalWrite(ROW[4], LOW);    // row 5 
  digitalWrite(ROW[5], HIGH);   // row 6 
  digitalWrite(ROW[5], LOW);    // row 6 
  digitalWrite(ROW[6], HIGH);   // row 7
  digitalWrite(ROW[6], LOW);    // row 7 
  digitalWrite(COL[3], 255);    // empty space between feet
  digitalWrite(ROW[7], HIGH);   // row 8  
  digitalWrite(COL[2], 0);      // left foot  
  digitalWrite(COL[4], 0);      // right foot
  digitalWrite(ROW[7], LOW);    // row 8 
  digitalWrite(COL[2], 255);    // col 3 
  digitalWrite(COL[4], 255);    // col 5 
}

// Display Leddy with his arms down
void armsDown()
{

  for (int i = 0; i < 6; i++)
  {
    analogWrite(COL[i], 255); // col i  - ANALOG
  }

  digitalWrite(ROW[3], HIGH);   // row 4 
  digitalWrite(COL[3], 0);      // head
  digitalWrite(ROW[3], LOW);    // row 4 - head
  digitalWrite(ROW[4], HIGH);   // row 5 - neck 
  digitalWrite(COL[2], 0);      // left shoulder
  digitalWrite(COL[4], 0);      // right shoulder
  digitalWrite(COL[2], 255);    // left shoulder
  digitalWrite(COL[4], 255);    // right shoulder
  digitalWrite(ROW[4], LOW);    // row 5
  digitalWrite(ROW[5], HIGH);   // row 6
  digitalWrite(COL[1], 0);      // left hand 
  digitalWrite(COL[1], 255);    // left hand
  digitalWrite(COL[5], 0);      // right hand
  digitalWrite(COL[5], 255);    // right hand  
  digitalWrite(ROW[5], LOW);    // row 6
  digitalWrite(ROW[6], HIGH);   // row 7 
  digitalWrite(ROW[6], LOW);    // row 7 
  digitalWrite(COL[3], 255);    // empty space between feet  
  digitalWrite(ROW[7], HIGH);   // row 8  
  digitalWrite(COL[2], 0);      // left foot  
  digitalWrite(COL[4], 0);      // right foot
  digitalWrite(ROW[7], LOW);    // row 8
  digitalWrite(COL[2], 255);    // left foot
  digitalWrite(COL[4], 255);    // right foot
}

// Display Leddy with his left arm up
void leftArmUp()
{

  for (int i = 0; i < 6; i++)
  {
    analogWrite(COL[i], 255); // col i  - ANALOG
  }

  digitalWrite(ROW[3], HIGH);   // row 4 
  digitalWrite(COL[3], 0);      // head
  digitalWrite(COL[1], 0);      // left hand  
  digitalWrite(COL[1], 255);    // left hand
  digitalWrite(ROW[3], LOW);    // row 4 - head
  digitalWrite(ROW[4], HIGH);   // row 5 - neck 
  digitalWrite(COL[2], 0);      // left shoulder
  digitalWrite(COL[4], 0);      // right shoulder
  digitalWrite(COL[2], 255);    // left shoulder
  digitalWrite(COL[4], 255);    // right shoulder
  digitalWrite(ROW[4], LOW);    // row 5
  digitalWrite(ROW[5], HIGH);   // row 6
  digitalWrite(COL[5], 0);      // right hand
  digitalWrite(COL[5], 255);    // right hand    
  digitalWrite(ROW[5], LOW);    // row 6
  digitalWrite(ROW[6], HIGH);   // row 7
  digitalWrite(ROW[6], LOW);    // row 7 
  digitalWrite(COL[3], 255);    // empty space between feet
  digitalWrite(ROW[7], HIGH);   // row 8
  digitalWrite(COL[2], 0);      // left foot
  digitalWrite(COL[4], 0);      // right foot
  digitalWrite(ROW[7], LOW);    // row 8
  digitalWrite(COL[2], 255);    // left foot
  digitalWrite(COL[4], 255);    // right foot
}

// Display Leddy with his right arm up
void rightArmUp()
{
  for (int i = 0; i < 6; i++)
  {
    analogWrite(COL[i], 255); // col i  - ANALOG
  }

  digitalWrite(ROW[3], HIGH);   // row 4
  digitalWrite(COL[5], 0);      // right hand
  digitalWrite(COL[5], 255);    // right hand
  digitalWrite(COL[3], 0);      // head
  digitalWrite(ROW[3], LOW);    // row 4 - head
  digitalWrite(ROW[4], HIGH);   // row 5 - neck 
  digitalWrite(COL[2], 0);      // left shoulder
  digitalWrite(COL[4], 0);      // right shoulder
  digitalWrite(COL[2], 255);    // left shoulder
  digitalWrite(COL[4], 255);    // right shoulder
  digitalWrite(ROW[4], LOW);    // row 5
  digitalWrite(ROW[5], HIGH);   // row 6 
  digitalWrite(COL[1], 0);      // left hand
  digitalWrite(COL[1], 255);    // left hand  
  digitalWrite(ROW[5], LOW);    // row 6
  digitalWrite(ROW[6], HIGH);   // row 7
  digitalWrite(ROW[6], LOW);    // row 7 
  digitalWrite(COL[3], 255);    // empty space between fee
  digitalWrite(ROW[7], HIGH);   // row 8
  digitalWrite(COL[2], 0);      // left foot
  digitalWrite(COL[4], 0);      // right foot
  digitalWrite(ROW[7], LOW);    // row 8
  digitalWrite(COL[2], 255);    // left foot
  digitalWrite(COL[4], 255);    // right foot
}

// Display left, right, and both input LEDS 
void displayInput()
{
  for (int i = 0; i < 6; i++)
  {
    analogWrite(COL[i], 255); // col i  - ANALOG
  }

  digitalWrite(ROW[1], HIGH);  // row 2 

  if(symbolIndex == 0) // If input is up/both
  {
    digitalWrite(COL[2], 0);    // left input
    digitalWrite(COL[4], 0);    // right input
    digitalWrite(COL[2], 255);  // left input
    digitalWrite(COL[4], 255);  // right input
  }
  else if(symbolIndex == 2) // If input is left
  {
    digitalWrite(COL[2], 0);    // left input
    digitalWrite(COL[2], 255);  // left input
  }
  else if(symbolIndex == 3) // If input is right
  {
    digitalWrite(COL[4], 0);    // right input
    digitalWrite(COL[4], 255);  // right input
  }

  digitalWrite(ROW[1], LOW);  // row 2 
}


// SETUP ============================================ SETUP
void setup()
{
  // init rows, columns
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {pinMode(ROW[i], OUTPUT);}
  for (int i = 0; i < 6; i++){pinMode(COL[i], OUTPUT);}

  // Initialize input pins
  pinMode(UP, INPUT);    // UP pin is on d2
  pinMode(LEFT, INPUT);  // LEFT  pin is on d4
  pinMode(RIGHT, INPUT); // RIGHT pin is on d5

  pinMode(PIEZO_BUZZER, OUTPUT); // initialize piezo buzzer 

  Serial.print("    WELCOME!    \n\n");
  Serial.print(symbols[symbolIndex]);
  Serial.print("\n");

  //  WELCOME MUSIC
  // iterate over the notes of the welcomeMelody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / welcomeNoteDurations[thisNote];
    tone(PIEZO_BUZZER, welcomeMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(PIEZO_BUZZER);
  }
}

// LOOP =============================================== LOOP
void loop()
{
  // need to be continuously scanning for input but only updating symbol every TIME_INTERVAL otherwise
  if(timeCount < TIME_INTERVAL) // while still on the same timestep
  {
    timeCount++; 
  
    inputs[0] = digitalRead(UP);    // 0 or 1
    inputs[1] == 0; // initially, down was an input, but we removed its functionality
    inputs[2] = digitalRead(LEFT);  // 0 or 1
    inputs[3] = digitalRead(RIGHT); // 0 or 1
      
    for( int i = 0; i < 4; i++ ) // U D L R
    {
      if(inputs[i] >= 1) // if a button was pushed, move sprite
      {
        inputs[i] = 1; // this and the >= account for analog pins
        
        if(i == 0) // sprite UP
        {
          UP_pushed = true;
          DOWN_pushed = false;
          RIGHT_pushed = false;
          LEFT_pushed = false;
        }        
        if(i == 1)  // sprite DOWN
        {
          UP_pushed = false;
          DOWN_pushed = true;
          RIGHT_pushed = false;
          LEFT_pushed = false;  
        }
        if(i == 2)  // sprite LEFT
        {
          UP_pushed = false;
          DOWN_pushed = false;
          RIGHT_pushed = false;
          LEFT_pushed = true;
        }        
        if(i == 3)  // sprite RIGHT          
        {
          UP_pushed = false;
          DOWN_pushed = false;
          RIGHT_pushed = true;
          LEFT_pushed = false;
        }

        // if CORRECT button!
        if(symbols[i] == symbols[symbolIndex]) 
        {
          if(resolvedCorrect == false)
          {
            Serial.print("GREAT! You entered ");
            Serial.print(symbols[i]);
            Serial.print("\n");

            // PLAY ERROR SOUND
            for (int thisNote = 0; thisNote < 6; thisNote++) {
              int correctNoteDuration = 1000 / correctNoteDurations[thisNote];
              tone(PIEZO_BUZZER, correctSound[thisNote], correctNoteDuration);          
              int pauseBetweenNotes = correctNoteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(PIEZO_BUZZER);
            }
          }
          resolvedCorrect = true;
        }
        
        else // if WRONG button
        {
          if(resolvedIncorrect == false)
          {
            // play an error sound or something 
            Serial.print("Keep trying... you entered ");
            Serial.print(symbols[i]);
            Serial.print("\n");

            // PLAY ERROR SOUND
            for (int thisNote = 0; thisNote < 2; thisNote++) {
              int errorNoteDuration = 1000 / errorNoteDurations[thisNote];
              tone(PIEZO_BUZZER, errorSound[thisNote], errorNoteDuration);          
              int pauseBetweenNotes = errorNoteDuration * 1.30;
              delay(pauseBetweenNotes);
              noTone(PIEZO_BUZZER);
            }
          }
          resolvedIncorrect = true;
        }
      }
    }  

    // must do this EVERY LOOP to keep sprite continually displayed
    displayInput();
    if(UP_pushed)    {armsUp();}     // i == 0
    if(DOWN_pushed)  {armsDown();}   // i == 1
    if(LEFT_pushed)  {leftArmUp();}  // i == 2
    if(RIGHT_pushed) {rightArmUp();} // i == 3 

  }

  
  else // End of this timestep; resolve it 
  {
    patternIt++; // Iterate thru pattern array
    patternIt = patternIt % 12; // CHANGE LENGTH IF CHANGE PATTERN
    symbolIndex = pattern2[patternIt];  

    // Score counter that we didn't end up fully implementing
    if(resolvedCorrect == true)
    {
      score++; 
      //Serial.print("SCORE: ");
      //Serial.print(score);
      //Serial.print("\n");
    } 
    else
    {
      // Serial.print("Keep trying :) \n");
    }
    
    Serial.print(symbols[symbolIndex]); // print new symbol
    Serial.print("\n"); // print new symbol 
    resolvedCorrect = false;
    resolvedIncorrect = false;
    timeCount = 0; // new time interval so reset counter 
  }  
}
