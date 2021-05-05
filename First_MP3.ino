#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "FastLED.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
void lights();
void sounds();

# define ACTIVATED LOW
int buttonNew = 5;
int buttonNext = A2;
int buttonPause = A3;
int buttonPrevious = 4;
int volumeControl = A0;
int volumeValue = 0;
bool isPlaying = false;
int P_E = 9;
int Rec = 8;
int LEDtoggle = A4 ;
bool LEDon = false;
int lightControl = A1;
int lightValue = 0;
int playThree = 12;
int playFour = 3;
int P_ETwo = 7;
int recTwo = 6;
int controlTwo = 2;

#define LEDpin 13
#define LEDnum 30

CRGB leds[LEDnum];

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(15);  //Set volume value. From 0 to 30

pinMode(buttonNew, INPUT);
digitalWrite(buttonNew,HIGH);
pinMode(buttonPause, INPUT);
digitalWrite(buttonPause,HIGH);
pinMode(buttonNext, INPUT);
digitalWrite(buttonNext,HIGH);
pinMode(buttonPrevious, INPUT);
digitalWrite(buttonPrevious,HIGH);
pinMode(P_E, INPUT);
pinMode(Rec, INPUT);
pinMode(LEDtoggle, INPUT);
digitalWrite(LEDtoggle, HIGH);
pinMode(playThree, INPUT);
digitalWrite(playThree,HIGH);
pinMode(playFour, INPUT);
digitalWrite(playFour,HIGH);
pinMode(controlTwo, INPUT);
digitalWrite(controlTwo,HIGH);
pinMode(P_ETwo, INPUT);
pinMode(recTwo, INPUT); 

FastLED.addLeds<WS2812, LEDpin, GRB>(leds, LEDnum);

delay(5000);
}

void loop()
{
  sounds();
  lights();
}

void lights()
{
lightValue = analogRead(lightControl)/5 ;

if ((digitalRead(LEDtoggle) == ACTIVATED) && (LEDon == false))
{
  delay(500);
  LEDon = true;
  delay(500);
}
if ((digitalRead(LEDtoggle) == ACTIVATED) && (LEDon == true))
{
  delay(500);
  LEDon = false;
  for (int i = 29; i >= 0; i--) 
  {
  leds[i] = CRGB ( 0, 0, 0);
  FastLED.show();
  }
  delay(500);
}

if (LEDon == true)
{
  for (int i = 0; i <= 9; i++)
  {
    leds[i+20] = CRGB ( lightValue, lightValue, 255);
    leds[i+10] = CRGB ( lightValue, lightValue, 255);
    leds[i] = CRGB ( lightValue, lightValue, 255);
    FastLED.show();
    delay(20);
  }
  for (int i = 0; i <= 9; i++) 
  {
    leds[i+20] = CRGB ( 255, lightValue, lightValue);
    leds[i+10] = CRGB ( 255, lightValue, lightValue);
    leds[i] = CRGB ( 255, lightValue, lightValue);
    FastLED.show();
    delay(20);
  }
  for (int i = 0; i <= 9; i++) 
  {
    leds[i+20] = CRGB ( lightValue, 255, lightValue);
    leds[i+10] = CRGB ( lightValue, 255, lightValue);
    leds[i] = CRGB ( lightValue, 255, lightValue);
    FastLED.show();
    delay(20);
  }
}
}


void sounds()
{
volumeValue = analogRead(volumeControl)/35 ;
myDFPlayer.volume(volumeValue);
digitalWrite(Rec, LOW);
digitalWrite(P_E, LOW);  
digitalWrite(recTwo, LOW);
digitalWrite(P_ETwo, LOW);

while ((digitalRead(buttonNew) == ACTIVATED) && (isPlaying == false))
{
  delay(200);
  while ((digitalRead(buttonPrevious) == ACTIVATED) && (isPlaying == false))
  {
    digitalWrite(Rec, HIGH);
  } 
  while ((digitalRead(controlTwo) == ACTIVATED) && (isPlaying == false))
  {
    digitalWrite(recTwo, HIGH);
  }
  delay(200);
}
if ((digitalRead(buttonNext) == ACTIVATED) && (isPlaying == false))
{
  delay(500);
  myDFPlayer.play(1);
  isPlaying = true;
  delay(500);
}
if ((digitalRead(buttonPause) == ACTIVATED) && (isPlaying == false))
{
  delay(500);
  myDFPlayer.play(2);
  isPlaying = true;
  delay(500);
}
if ((digitalRead(buttonPrevious) == ACTIVATED) && (isPlaying == false))
{
  digitalWrite(P_E, HIGH); 
  delay(100); 
  digitalWrite(P_E, LOW); 
  delay(1000); 
}
if ((digitalRead(controlTwo) == ACTIVATED) && (isPlaying == false))
{
  digitalWrite(P_ETwo, HIGH); 
  delay(100); 
  digitalWrite(P_ETwo, LOW); 
  delay(1000); 
}
if ((digitalRead(playThree) == ACTIVATED) && (isPlaying == false))
{
  delay(500);
  myDFPlayer.play(3);
  isPlaying = true;
  delay(500);
}
if ((digitalRead(playFour) == ACTIVATED) && (isPlaying == false))
{
  delay(500);
  myDFPlayer.play(4);
  isPlaying = true;
  delay(500);
}
if ((digitalRead(buttonNext) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
if ((digitalRead(buttonPause) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
if ((digitalRead(buttonPrevious) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
if ((digitalRead(buttonNew) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
if ((digitalRead(playThree) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
if ((digitalRead(playFour) == ACTIVATED) && (isPlaying == true))
{
  delay(500);
  myDFPlayer.pause();
  isPlaying = false;
}
}
