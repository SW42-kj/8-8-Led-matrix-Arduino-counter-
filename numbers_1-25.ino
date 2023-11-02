#include <avr/pgmspace.h>
#include <LedControl.h>

#define button 2

LedControl display = LedControl(12, 11, 10, 1);

int numberToDisplay = 0;

const uint64_t NUMBERS[] PROGMEM = {
  0xbdc3663c99c3e7ff,  // 0
  0x000e040404060400,  // 1
  0x001e02040810120c,  // 2
  0x0c12100c1010120c,  // 3
  0x00103e1214181000,  // 4
  0x000e10100e021e00,  // 5
  0x000c12120e02120c,  // 6
  0x0004040408101e00,  // 7
  0x0c12120c12120c00,  // 8
  0x0c12101c12120c00,  // 9
  0x00f792929293f200,  // 10
  0x0077222222332200,  //11
  0x00f712224293e200,  //12
  0x00679282e2839260,  //13
  0x004742fa52634200,  //14
  0x007782827213f200,   //15
  0x0067927212936200,   //16
  0x002722222243f200,   //17
  0x00f792f29293f200,  //18
  0x007782e292936200,  //19
  0x00efa1a2a4a9e600,  //20
  0x00ef414244694600,  //21
  0x00f7214284956600,   //22
  0x6097816284956600,   //23
  0x004741fa54654600,   //24
  0x007781827415f600,  //25
  0xffffffffffffffff,  //blanck
};

void setup() {
  pinMode(button, INPUT);
  display.shutdown(0, false);
  display.setIntensity(0, 3);
  display.clearDisplay(0);
}

void displayNumber(int num) {
  if (num >= 0 && num <= 40) {
    displayImage((uint64_t*)&NUMBERS[num]);
  }
}

void displayImage(uint64_t* pImage) {
  byte* p = (byte*)pImage;
  for (int i = 0; i < 8; ++i) {
    byte row = pgm_read_byte(p++);
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bool(row & 1));
      row >>= 1;
    }
  }
}

void loop() {
  if (digitalRead(button) == 1) {
    do {
      delay(20);
    } while (digitalRead(button) == 1);

    // Increment the number to be displayed
    numberToDisplay++;
    if (numberToDisplay > 40) {
      numberToDisplay = 0;
    }

    displayNumber(numberToDisplay);
  }

  delay(100);
}
