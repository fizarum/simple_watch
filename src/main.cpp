#include <Arduino.h>

#include "dev/dev_controller.h"

#define REFRESH_DELAY 5000

void init_button();
unsigned long getLastRefreshDisplayTime();

volatile bool showDisplay = false;
unsigned long lastDisplayRefreshTime = 0;
DevController *deviceController;
/////

void setup() {
    Serial.begin(9600);

    deviceController = new DevController();

    deviceController->init();
    init_button();
}

void loop() {
    deviceController->getDisplay()->setEnabled(showDisplay);

    if(deviceController->getDisplay()->isEnabled() &&
        getLastRefreshDisplayTime() >= REFRESH_DELAY) {
            deviceController->getDisplay()->update();
            lastDisplayRefreshTime = millis();
            const char * time = deviceController->getRtc()->timeStr();
            const char *date = deviceController->getRtc()->dateStr();
            deviceController->getDisplay()->text(time, 3, DisplayST7735::colorGreen, 20, 40);
            deviceController->getDisplay()->text(date, 1, DisplayST7735::colorBlue, 70, 100);
            free((void*)time);
            free((void*)date);
        }
}

void toggleDisplay() {
    showDisplay = !showDisplay;
}

void init_button() {
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), toggleDisplay, RISING);
}

unsigned long getLastRefreshDisplayTime() {
    if(lastDisplayRefreshTime == 0) {
        lastDisplayRefreshTime = millis();
        return 0;
    }

    return millis() - lastDisplayRefreshTime;
}