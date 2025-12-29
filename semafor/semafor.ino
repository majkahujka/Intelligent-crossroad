#include <Wire.h>
#include "RTClib.h"

// =================== TLACIDLA – 4 PRERUSENIA ====================
const byte button1Pin  = 2;   // externé prerušenie
const byte button2Pin  = 3;   // externé prerušenie
const byte button3Pin  = 18;  // externé prerušenie
const byte button4Pin  = 19;  // externé prerušenie

volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool button3Pressed = false;
volatile bool button4Pressed = false;

bool stav0 = false;
bool stav1 = false;
bool stav2 = false;
bool stav3 = false;

// =================== SEMAFORY A LEDKY ====================
int cas  = 1000;
int cas1 = 5000;

// =================== RTC ====================
RTC_DS3231 rtc;
String serialBuffer = "";

// =================== SETUP ====================
void setup() {
  Serial.begin(9600);
  delay(2000);

  // Tlacidla – spínace sú normálne v GND, po stlačení HIGH
  // => použijeme INPUT_PULLUP + prerušenie na RISING
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);

  pinMode(A10,INPUT);
  pinMode(A8,INPUT);

  for (int i = 22; i < 54; i++) {
    pinMode(i, OUTPUT);
  }

  // Prerusenia – reagujú na nábežnú hranu (LOW -> HIGH)
  attachInterrupt(digitalPinToInterrupt(button1Pin), onButton1Interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), onButton2Interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(button3Pin), onButton3Interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(button4Pin), onButton4Interrupt, RISING);

  Serial.println("System start. Prikazy: tHH:MM:SSdDD.MM.RRRR alebo a");
  digitalWrite(28,HIGH);
  digitalWrite(29,HIGH);
  
}

// =================== ISR – IBA NASTAVIA PRIZNAKY ====================

void onButton1Interrupt() { button1Pressed = true; }
void onButton2Interrupt() { button2Pressed = true; }
void onButton3Interrupt() { button3Pressed = true; }
void onButton4Interrupt() { button4Pressed = true; }

// =================== LOOP ====================
void loop() {

  readSerialCommands();
  handleButtons();

  if(analogRead(A0) > 500)
  {
    blik();
    verejne();
  }
  else
  {
    handleButtons();
    scenar1();
    readSerialCommands();
    handleButtons();
    scenar2();
    readSerialCommands();
    handleButtons();
    scenar3();
  }  
}

// =================== SPRACOVANIE TLACIDIEL ====================
void handleButtons() {
  if (button1Pressed) {
    button1Pressed = false;
    stav0 = true;
    // Sem môžeš napr. volať nejaku akciu: SEM1(stav0);
  }

  if (button2Pressed) {
    button2Pressed = false;
    stav1 = true;
  }

  if (button3Pressed) {
    button3Pressed = false;
    stav2 = true;
  }

  if (button4Pressed) {
    button4Pressed = false;
    stav3 = true;
  }
}


