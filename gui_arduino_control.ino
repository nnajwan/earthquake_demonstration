#include <SPI.h>
#include <SD.h>

File myFile;
int STEP = 3;
int DIR = 5;
int ARR[200];
int i;
long n;

int incomingByte;      // variable stores  serial data

void setup() {
  // initialize serial communication:
  pinMode (STEP, OUTPUT);
  pinMode (DIR, OUTPUT);
  Serial.begin(9600);

  while (!Serial)
  {
    ; // wait for serial port to connect
  }

  if (!SD.begin(10))
  {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done!");

}
  
void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      myFile = SD.open("Light.txt");
    }
    if (incomingByte == 'L') {
      myFile = SD.open("Medium.txt");
    }
    if (incomingByte == 'M') {
      myFile = SD.open("MHigh.txt");
    }
  if (myFile){
    while (myFile.available())
    {
      for (i=0; i<200; i++)
      {
        ARR[i] = (myFile.parseInt());
        
        if (ARR[i]>0)
        {
          digitalWrite(DIR, 1);
        }

        else {
          digitalWrite(DIR,0);
        }

        long N = abs(ARR[i]/7.5);
        long Duree = abs(375000/ARR[i]);

        for (n=0; n<N; n++)
        {
          digitalWrite(STEP, 1);
          delayMicroseconds(Duree);
          digitalWrite(STEP,0);
          delayMicroseconds(Duree);
        }
      }
    }
  }
  }
}
