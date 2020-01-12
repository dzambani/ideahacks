#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <string.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128   
#define SCREEN_HEIGHT 64   

char eq1[] = "2 + 3 = 5"; 
char eq2[] = "sin(0) + cos(0) + tan(pi)= 2";
char eq3[] = "log(100) - 3 = -1";

int state = 1;

Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()   {

  Serial.begin(9600);
  Serial.println("Start!");

  int fail = 0;


  while (!display1.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed for display 1"));
    fail++;
  }

  if (fail)
    for(;;);
  else
    Serial.println("Allocation successful");
  
  delay(2000);
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0, 10);
  display1.println(eq1);
  display1.display();   
  delay(2000);
  state++;
}

void loop() {

  if(false) {
    display1.clearDisplay();
    display1.setCursor(0, 10);
  }
  switch(state)
  {
    case 1:
      display1.println(eq1);
      state++;
      break;
    case 2:
      display1.println(eq2);
      state++;
      break;
    case 3:
      display1.println(eq3);
      state = 1;
      break;
    default:
      break;
  }
  display1.display();
  delay(2000);
}
