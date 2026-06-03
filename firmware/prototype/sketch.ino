#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define DOWN_BTN  1
#define UP_BTN    2
#define RIGHT_BTN 3
#define LEFT_BTN  4
#define ACT_BTN   15

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String lastAction = "Ready!";
String lastBtn    = "";

struct BtnDef {
  int pin;
  const char* label;
  const char* action;
};

BtnDef buttons[] = {
  { DOWN_BTN,  "DOWN",  "Moving DOWN"  },
  { UP_BTN,    "UP",    "Moving UP"    },
  { RIGHT_BTN, "RIGHT", "Moving RIGHT" },
  { LEFT_BTN,  "LEFT",  "Moving LEFT"  },
  { ACT_BTN,   "ACT",   "ACTION!"      },
};

const int NUM_BUTTONS = sizeof(buttons) / sizeof(buttons[0]);

void showOLED(const char* btnName, const char* actionText){
  display.clearDisplay();

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(4, 3);
  display.print("ESP32-C6 Controller");

  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  int nameLen = strlen(btnName) * 12;
  display.setCursor((SCREEN_WIDTH - nameLen) / 2, 20);
  display.print(btnName);

  display.setTextSize(1);
  int actionLen = strlen(actionText) * 6;
  display.setCursor((SCREEN_WIDTH - actionLen) / 2, 47);
  display.print(actionText);

  display.display(); 
}

void setup(){
  Serial.begin(115200);

  for(int i = 0; i < NUM_BUTTONS; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  Wire.begin(6,7);
  if(!display.begin(0x3C, true)){
    Serial.print("Init failed");
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (digitalRead(buttons[i].pin) == LOW) {
      if (lastBtn != buttons[i].label) {          
        lastBtn    = buttons[i].label;
        lastAction = buttons[i].action;
        Serial.println(lastAction);
        showOLED(buttons[i].label, buttons[i].action);
      }
      delay(10);
      return;                                    
    }
  }
  lastBtn = ""; 
  delay(10);
}