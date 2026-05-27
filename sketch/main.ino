#include <Arduino.h>
#include <U8g2lib.h>

// This pin maps to the space key in the simulator
#define PIN_SNAPSHOT 2 

// Standard U8g2 constructor
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

bool snapshotMode = false;
int lastBtnState = HIGH;
int snapX = 0, snapY = 0;
unsigned long lastMillis = 0;

static void drawFilledSquare(int x, int y, int size) {
    int half = size / 2;
    for (int i = x - half; i < x + half; i++) {
        for (int j = y - half; j < y + half; j++) {
            u8g2.drawPixel(i, j);
        }
    }
}

void setup() {
    Serial.begin(9600);
    u8g2.begin();
    u8g2.setFont(u8g2_font_5x7_tr);
    pinMode(PIN_SNAPSHOT, INPUT_PULLUP);
    Serial.println("Simulator Started");
}

void loop() {
    // Report frame rate info every second
    if (millis() - lastMillis >= 1000) {
        Serial.print("Simulation FrameRate: ");
        Serial.println(simFrameRate);
        lastMillis = millis();
    }

    // Arduino-style button toggle logic
    int btnState = digitalRead(PIN_SNAPSHOT);
    if (btnState == LOW && lastBtnState == HIGH) {
        snapshotMode = !snapshotMode;
        u8g2.clearDisplay();
    }
    lastBtnState = btnState;

    // Use standard analogRead for inputs
    int valX = analogRead(A0);
    int valY = analogRead(A1);
    
    int logicMouseX = (valX * 128) / 1024;
    int logicMouseY = (valY * 64) / 1024;

    if (u8g2.pageIndex == 0) {
        if (snapshotMode) {
            snapX = logicMouseX;
            snapY = logicMouseY;
        }
    }

    if (snapshotMode) {
        drawFilledSquare(snapX, snapY, 20);
        u8g2.drawStr(2, 8, "S");
    } else {
        drawFilledSquare(logicMouseX, logicMouseY, 20);
        u8g2.drawStr(2, 8, "R");
    }
}
