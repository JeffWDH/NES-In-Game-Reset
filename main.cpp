/*
NES In Game Reset
Press Select and Start simultaneously to reset the console
https://www.tarball.ca/posts/nes-in-game-reset-arduino/

Thanks to the Nintendo controller documentation by Bitluni:
https://bitluni.net/gamepad

Pins in use:
A0 - Clock (Input)
A1 - Latch (Input)
A2 - Data (Input)
A3 - Reset (Ouput)

NES Controller Port Pinout:
+---------+
| 5  6  7   \     
| 4  3  2  1 |    
+------------+ 
1 - Ground
2 - Clock
3 - Latch
4 - Data
7 - +5V

On the power / reset PCB the pin marked "4" should be
connected to pin A3 (reset).
*/

#include <Arduino.h>

// Button definitions
const int buttonA = 0;
const int buttonB = 1;
const int buttonSelect = 2;
const int buttonStart = 3;
const int buttonUp = 4;
const int buttonDown = 5;
const int buttonLeft = 6;
const int buttonRight = 7;

// Variables
int buttonState[7]; // 8 bits for button state

void setup() {
  pinMode(A0, INPUT); // Clock
  pinMode(A1, INPUT); // Latch
  pinMode(A2, INPUT); // Data
  pinMode(A3, OUTPUT); // Reset
}

// digitalRead is too slow hence the direct port reads below

int clockState() {
  int state = (PINC&(1<<(0))); // Direct "digitalRead" A0
  if (state) { // Anything other than 0 is HIGH
    return HIGH;
  } else {
    return LOW;
  }
}

int latchState() {
  int state = (PINC&(1<<(1))); // Direct "digitalRead" A1
  if (state) { // Anything other than 0 is HIGH
    return HIGH;
  } else {
    return LOW;
  }
}

int dataRead() {
  int data = (PINC&(1<<(2))); // Direct "digitalRead" A2
  return data;
}

void clockFalling() {
  while (clockState() == LOW) {
    // Wait until HIGH
  }
  while (clockState() == HIGH) {
    // Wait until LOW
  }
}

void latchFalling() {
  while (latchState() == LOW) {
    // Wait until HIGH
  }
  while (latchState() == HIGH) {
    // Wait until LOW
  }
}

void loop() {  
  latchFalling(); // Wait for latch to go low

  // Capture the 8 button states
  for (int i = 0; i < 8; i++) {  
    // Wait for clock to go low then read button data
    clockFalling();
    buttonState[i] = dataRead();
  }

  // If Select and Start buttons are pressed simultaneously
  // then reset the console.
  if (buttonState[buttonSelect] == 0 and buttonState[buttonStart] == 0) {
    // Set reset pin high to stop console
    digitalWrite(A3, HIGH);
    delay(3000);

    // Set reset pin low to start up
    digitalWrite(A3, LOW);
    delay(500); 
  }
}