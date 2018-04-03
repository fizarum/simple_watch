#include <Arduino.h>

#include "ui/ui_controller.h"
#include "dev/dev_controller.h"
#include "dev/input_controller.h"
#include "utils.h"

#define REFRESH_DELAY 5000

unsigned long getLastRefreshDisplayTime();
unsigned long lastDisplayRefreshTime = 0;

const gpio_num_t menuButtonPin = GPIO_NUM_13;

DevController *deviceController = new DevController();
UIController *uiController = new UIController();
InputController *inputController = new InputController(menuButtonPin);

void setup() {
    
    set_cpu_speed_down();

    deviceController->init();
    inputController->init();
    //init_button();
    Serial.begin(115200);
}

void loop() {
    deviceController->getDisplay()->setEnabled(showDisplay);
    if(deviceController->getDisplay()->isEnabled() &&
        getLastRefreshDisplayTime() >= REFRESH_DELAY) {
            Serial.printf("time to update\n freq: %d\n", get_cpu_freq());
            deviceController->getDisplay()->update();
            lastDisplayRefreshTime = millis();

            // deviceController->getDisplay()->text("Hello", 3, DisplayST7735::colorGreen, 20, 40);
            // deviceController->getDisplay()->text("world", 1, DisplayST7735::colorBlue, 70, 100);
            
            char text[20];
            get_cpu_freq_str(text, get_cpu_freq());
            //sprintf(text, "frq: %d", get_cpu_freq());
            deviceController->getDisplay()->text(text, 1, DisplayST7735::colorRed, 10, 10);
        }
}

unsigned long getLastRefreshDisplayTime() {
    if(lastDisplayRefreshTime == 0) {
        lastDisplayRefreshTime = millis();
        return REFRESH_DELAY;
    }

    return millis() - lastDisplayRefreshTime;
}