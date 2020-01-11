#include <Keypad.h>
//pwm pins reserved 3, 5, 6, 11

const byte ROWS = 5; 
const byte COLS = 5; 
char firstShift[ROWS][COLS] = {
  {'o','s','c','t','/'}, // s c t are trig functions, l is log 
  {'l','7','8','9','*'}, //x is exponent, p is pi, n is e, o is on
  {'x','4','5','6','-'},
  {'n','1','2','3','+'},
  {'p','.','0','_','e'} //_ is negative, e is enter, second funcion for 0 is ( and . is )
};

char secondShift[ROWS][COLS] = {
  {'o','s','c','t','/'}, //s, c, t are arc trig, l is 10^
  {'l','7','8','9','*'}, //x is squared, n is ln, o is off
  {'x','4','5','6','-'},
  {'n','1','2','3','+'},
  {'p','.','0','_','e'} //_ is answer, e is enter, p is (, and . is )
};
byte rowPins[ROWS] = {7, 4, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 10, 9, 8}; //connect to the column pinouts of the keypad

Keypad firstpad = Keypad(makeKeymap(firstShift), rowPins, colPins, sizeof(rowPins), sizeof(colPins));
Keypad secondpad = Keypad(makeKeymap(secondShift), rowPins, colPins, sizeof(rowPins), sizeof(colPins));

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){
        case '#': digitalWrite(ledPin,!digitalRead(ledPin)); break;
        case '*':
          digitalWrite(ledPin,!digitalRead(ledPin));
        break;
      }
    break;
    case RELEASED:
      switch (key){
        case '*':
          digitalWrite(ledPin,!digitalRead(ledPin));
          blink = false;
        break;
      }
    break;
    case HOLD:
      switch (key){
        case '*': blink = true; break;
      }
    break;
  }
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  keypad.setHoldTime(500);
  keypad.setDebounceTime(250);
}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
