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

  int encB_last = 1;
  int encA_last = 1;

  int previous[4][5];
  bool currentState[4][5];
  uint8_t debounceCount[4][5];

  void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    pinMode(encA, INPUT_PULLUP);
    pinMode(encB, INPUT_PULLUP);
    pinMode(encSW, INPUT_PULLUP);
    for (int j = 0; j < 4; j++) {
    pinMode(rowPins[j], OUTPUT);
    digitalWrite(rowPins[j], HIGH);
    pinMode(colPins[j], INPUT_PULLUP);
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        previous[i][j] = 1;
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        currentState[i][j] = 1;
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        debounceCount[i][j] = 1;
      }
    }
  }

  void loop() {
    for (int i = 0; i < 4; i++) {
      digitalWrite(rowPins[i], LOW);
      for (int j = 0; j < 4; j++){
        int read = digitalRead(colPins[j]);
        if(previous[i][j] == read){
          if(debounceCount[i][j] < 255) debounceCount[i][j]++;
        }
        else if(previous[i][j] != read){
          debounceCount[i][j] = 0;
        }        
        if(debounceCount[i][j] == 50 && currentState[i][j] == 1 && read == 0){
          Serial.println("Button was pressed");
          Keyboard.press(keymap[i][j]);
          currentState[i][j] = 0;
        }
        else if(debounceCount[i][j] == 50 && currentState[i][j] == 0 && read == 1){
          Serial.println("Button was released");
          Keyboard.release(keymap[i][j]);
          currentState[i][j] = 1;
        }
        previous[i][j] = read;
      }
      digitalWrite(rowPins[i], HIGH);
    }

    int encA_now = digitalRead(encA);
    int encB_now = digitalRead(encB);

    if(encA_now == 0 && encA_last == 1 && encB_now == 1 && encB_last == 1){
      Serial.println("Clockwise");
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
    }
    if(encA_now == 1 && encA_last == 1 && encB_now == 0 && encB_last == 1){
      Serial.println("Anticlockwise");
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
    }

    int read2 = digitalRead(encSW);
    if (read2 == previous[3][4]){
      if(debounceCount[3][4] < 255) debounceCount[3][4]++;
    }  
    else if (read2 != previous[3][4]){
      debounceCount[3][4] = 0;
    }

    if(debounceCount[3][4] == 50 && currentState[3][4] == 1 && read2 == 0) {
      Serial.println("Button pressed");
      currentState[3][4] = 0;
      Keyboard.press('p');
    }
    else if(debounceCount[3][4] == 50 && currentState[3][4] == 0 && read2 == 1){
      Serial.println("Button released");
      currentState[3][4] = 1;
      Keyboard.release('p');
    }

    previous[3][4] = read2;
    encA_last = encA_now;
    encB_last = encB_now;
  }
