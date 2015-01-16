/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

const int firingOrder[] = {
  12, 8, 3, 6, 4, 5, 2, 7
};
const int sensorPin = A0;

int sensorValue = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
  // initialize digital pin 13 as an output.
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

float RPM = 600;
int index = 0;

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(sensorPin);
  float percentValue = sensorValue / 1023.0;
  RPM = 9000 * percentValue;

  // Engine Stalling
  if (RPM < 50) { 
    noTone(11);
    return;
  }
  
  float dominantFrequency = getFrequency(RPM);
  Serial.println(dominantFrequency);

  noTone(11);
  tone(11, dominantFrequency);
    
  float strokeTime = 1000/(RPM/60.0);
  
  digitalWrite(firingOrder[index], HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(strokeTime/2);              
  digitalWrite(firingOrder[index], LOW);    // turn the LED off by making the voltage LOW
  delay(strokeTime/2);

  index++;
  if (index > 7) {
    index = 0;
  }
}

void printRPM(float rpm) {
  Serial.print(RPM);
  Serial.print(" ");
  Serial.print(RPM/60.0);
  Serial.print(" ");
  Serial.println(1000/(RPM/60.0));
}

float getFrequency(float rpm) {
  float hertz = rpm/60.0;
  float dominantFrequency = hertz * 4;
  return dominantFrequency;
}
