#include "Keyboard.h"

const int rowPins[4] = {10, 9, 7, 6};
const int colPins[4] = {11, 8, 5, 4};
char keymap[4][4] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'a', 'b'},
  {'c', 'd', 'e', 'f'}
};


const int encA = 3;
const int encB = 2;
const int encSW = 1;

  int previous[4][4] = {0};


  bool currentState[4][4];

  uint8_t debounceCount[4][4];

void setup() {
  Serial.begin(115200);
  for (int j = 0; j < 4; j++) {
  pinMode(rowPins[j], OUTPUT);
  pinMode(colPins[j], INPUT_PULLUP);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
    previous[i][j] = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
    currentState[i][j] = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
    debounceCount[i][j] = 1;
    }
  }

}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(rowPins[i], LOW);
    for (int j = 0; j < 4; j++){

      if(previous[i][j] == digitalRead()){
        debounceCount += 1;
      }
    }
  }
}
