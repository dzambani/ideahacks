#include <Keypad.h>
#include <math.h>
//pwm pins reserved 3, 5, 6, 11

const byte ROWS = 5; 
const byte COLS = 5; 
char firstShift[ROWS][COLS] = {
  {'w','s','c','t','/'}, //s c t are trig functions, w for timer/stopwatch
  {'x','7','8','9','*'}, //x is exponent
  {'n','4','5','6','-'}, //n is ln
  {'p','1','2','3','+'}, //p is pi
  {'b','.','0','_','e'} //b is 10^, _ is negative, e is enter
};

char secondShift[ROWS][COLS] = {
  {'f','s','c','t','/'}, //s, c, t are arc trig, f is fan
  {'l','7','8','9','*'}, //l is log
  {'q','4','5','6','-'}, //q is squared
  {'m','1','2','3','+'}, //m is e 
  {'(',')','0','a','e'} //a is answer
};
byte rowPins[ROWS] = {7, 4, 2, 1, 0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 10, 9, 8}; //connect to the column pinouts of the keypad

Keypad firstpad = Keypad(makeKeymap(firstShift), rowPins, colPins, sizeof(rowPins), sizeof(colPins));
Keypad secondpad = Keypad(makeKeymap(secondShift), rowPins, colPins, sizeof(rowPins), sizeof(colPins));

const int switchPin = 15; //the switch connect to pin 12
const int ledPin = 6;//the led connect to pin 6
int switchState = 0;  
const int motorPin = 3;

String calc = "";
int last_calc;
int input_state = 0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  firstpad.begin(makeKeymap(firstShift));
  secondpad.begin(makeKeymap(secondShift));
  firstpad.addEventListener(keypadEvent_first);  // Add an event listener.
  firstpad.setHoldTime(1000);                   // Default is 1000mS
  firstpad.setDebounceTime(250);
  secondpad.addEventListener(keypadEvent_second);  // Add an event listener.
  secondpad.setHoldTime(1000);                   // Default is 1000mS
  secondpad.setDebounceTime(250);
  pinMode(switchPin, INPUT); //initializethebuttonPin as input
  pinMode(ledPin, OUTPUT); //initialize the ledpin as output
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
}

char key;

void loop() {
  // put your main code here, to run repeatedly:
  switchState = digitalRead(switchPin);
  if (switchState == LOW) 
  {
    digitalWrite(ledPin, LOW); //turn the led off
    key = firstpad.getKey();
  }
  else 
  {
    digitalWrite(ledPin, HIGH); //turn the led off
    key = secondpad.getKey();
  }
  
  if (key)
    Serial.println(key);
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
  //return;
    switch(state) {
        case PRESSED:
          switch (key)
          {
            case '_':
              //display '-'
              calc += key;
              break;
            case 's':
              //include display code 
              if (switchState == LOW)
                calc += "sin(input)"; //program states
              else
                calc += "asin(input)";
              break;
            case 'c':
              //include display code 
              if (switchState == LOW)
                calc += "cos(input)"; //program states
              else
                calc += "acos(input)";
              break;
            case 't':
              //include display code 
              if (switchState == LOW)
                calc += "tan(input)"; //program states
              else
                calc += "atan(input)";
              break;
            case 'w':
              //include display code on other screen and switch input control to other screen 
              //run timer code 
              break;
            case 'f':
              digitalWrite(motorPin, !(digitalRead(motorPin));
              break;
            case 'x':
              if (!input_state) 
              {
                input_state = 2;
                //prompt for input
              }
            case 'l':
              if (!input_state) 
              {
                input_state = 2;
                //prompt for input
              }
            case 'n':
              if (!input_state) 
              {
                input_state++;
                //prompt for input
              }
            case 'q':
              if (!input_state) 
              {
                input_state++;
                //prompt for input
              }
            case 'm':
              //display 'e'
              calc += 'e';
            case 'b':
              if (!input_state) 
              {
                input_state++;
                //prompt for input
              }
            case 'e': 
              if (!input_state)
              {
                //parse_string() + calculate() --> sets last_calc 
              }
              else 
              {
                //wait for input 
                input_state--;
              }
              //state handling     
            default: 
              //display key 
              calc += key;
          }

        /*case HOLD:
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
            break;*/
        /*case RELEASED:
            if (buildCount >= sizeof(buildStr))  buildCount = 0;  // Our string is full. Start fresh.
            break;*/
    }  // end switch-case
}// end switch on state function

setTimer() 
{
  
}
