#include <Arduino.h>

// PWM control pin
#define PWM1_PIN            5                               // Left Motor Speed
#define PWM2_PIN            6                               // Right Motor Speed
// 74HCT595N Chip pins
#define SHCP_PIN            2                               // Clock Pin
#define EN_PIN              7                               // Output Enable
#define DATA_PIN            8                               // Serial data  
#define STCP_PIN            4                               // Latch Pin

// Solar Motor Pins
#define SOLAR1_PIN          A5
#define SOLAR2_PIN          11

#define debug               1

const int delayTime = 500;

// Motors config
//
//  M1  M3
//  M2  M4
//
// const int m1Forward  = B01000000;
// const int m1Backward = B10000000;

// const int m2Forward  = B00010000;
// const int m2Backward = B00100000;

// const int m3Forward  = B00000100;
// const int m3Backward = B00000010;

// const int m4Forward  = B00001000;
// const int m4Backward = B00000001;

// Directions can be seen by adding the binary vaules together
const int Forward       = 92;                              // forward                  - All Motors forward
const int Backward      = 163;                              // backward                 - All Motors Backwards
const int Stop          = 0;                               // stop                     - All Motors Stopped
const int CClockwise    = 172;                             // Rotate Counter Clockwise - M1 & M2 Backwards + M3 && M4 Forwards
const int Clockwise     = 83;                              // Rotate Clockwise         - M1 & M2 Forwards + M3 & M4 Backwards


void Motor(int Dir, int SpeedRight , int SpeedLeft)
{
  if (debug == true) {
    Serial.println(Dir, BIN);  // Prints the Shift registers command as binary to the console
  }

  analogWrite(PWM1_PIN, SpeedRight);
  analogWrite(PWM2_PIN, SpeedLeft);
  digitalWrite(EN_PIN, LOW);
  digitalWrite(STCP_PIN, LOW);
  shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
  digitalWrite(STCP_PIN, HIGH);
}

void setup()
{
    Serial.begin(9600);
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
    pinMode(SOLAR1_PIN, OUTPUT);
    pinMode(SOLAR2_PIN, OUTPUT);
}

void loop()
{
    /* Forward */
    Motor(Forward, 250,250);      
    delay(delayTime);

    /* Backward */
    Motor(Backward, 250,250);
    delay(delayTime);

    /* Counter Clockwise */
    Motor(CClockwise, 250,250);
    delay(delayTime);

    /* Clockwise */
    Motor(Clockwise, 250,250);
    delay(delayTime);

    /* Stop */
    Motor(Stop, 250,250);
    delay(2000);

    /* Solar Front */
    digitalWrite(SOLAR1_PIN, 0);
    digitalWrite(SOLAR2_PIN, 1);
    delay(delayTime);
    digitalWrite(SOLAR1_PIN, 0);
    digitalWrite(SOLAR2_PIN, 0);

    /* Solar Back */
    digitalWrite(SOLAR1_PIN, 1);
    digitalWrite(SOLAR2_PIN, 0);
    delay(delayTime);
    digitalWrite(SOLAR1_PIN, 0);
    digitalWrite(SOLAR2_PIN, 0);
}