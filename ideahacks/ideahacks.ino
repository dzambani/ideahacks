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
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  firstpad.begin(makeKeymap(firstShift));
  secondpad.begin(makeKeymap(secondShift));
  firstpad.addEventListener(keypadEvent_first);  // Add an event listener.
  firstpad.setHoldTime(500);                   // Default is 1000mS
  firstpad.setDebounceTime(250);
  secondpad.addEventListener(keypadEvent_second);  // Add an event listener.
  secondpad.setHoldTime(500);                   // Default is 1000mS
  secondpad.setDebounceTime(250);
}

char key;

void loop() {
  // put your main code here, to run repeatedly:
  if (!fs_switch) 
    key = firstpad.getKey();
  else 
    key = secondpad.getKey();
  
  if (key){
    Serial.println(key);
  }
}

static byte state;

void keypadEvent_first(KeypadEvent key){
  state = firstpad.getState();
  switcher(key);
}

void keypadEvent_second(KeypadEvent key){
  state = secondpad.getState();
  switcher(key);
}
  
void switcher(char key) {
    switch(state) {
        case PRESSED:
            if (isalpha(key)) {              // This is a letter key so we're using the letter keymap.
                if (physKey != key) {        // New key so start with the first of 3 characters.
                    pressCount = 0;
                    virtKey = key;
                    physKey = key;
                }
                else {                       // Pressed the same key again...
                    virtKey++;                   // so select the next character on that key.
                    pressCount++;                // Tracks how many times we press the same key.
                }
                    if (pressCount > 2) {    // Last character reached so cycle back to start.
                        pressCount = 0;
                        virtKey = key;
                    }
                    Serial.print(virtKey);   // Used for testing.
                }
                if (isdigit(key) || key == ' ' || key == '.')
                    Serial.print(key);
                if (key == '#')
                    Serial.println();
                break;

        case HOLD:
            if (key == '#')  {               // Toggle between keymaps.
                if (alpha == true)  {        // We are currently using a keymap with letters
                    alpha = false;           // Now we want a keymap with numbers.
                    digitalWrite(ledPin, LOW);
                }
                else  {                      // We are currently using a keymap with numbers
                    alpha = true;            // Now we want a keymap with letters.
                }
            }
            else  {                          // Some key other than '#' was pressed.
                buildStr[buildCount++] = (isalpha(key)) ? virtKey : key;
                buildStr[buildCount] = '\0';
                Serial.println();
                Serial.println(buildStr);
            }
            break;

        case RELEASED:
            if (buildCount >= sizeof(buildStr))  buildCount = 0;  // Our string is full. Start fresh.
            break;
    }  // end switch-case
}// end switch on state function
