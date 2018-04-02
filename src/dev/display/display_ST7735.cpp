#include "display_ST7735.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     16
#define TFT_RST    33
//A0
#define TFT_DC     17

#define TFT_SCLK 5
#define TFT_MOSI 23

#define TFT_LED 12
//minimal = 30
#define DEF_BRIGHTNESS 80   

/// pwm backlight part
#define PWM_FREQ 5000
#define PWM_BACKLIGHT_CHANNEL 0
#define PWM_RESOLUTION 8
#define PWM_BACKLIGHT_PIN 12
/// pwm ends

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void invalidateState(Display *display);
bool visible(Display *display);

uint16_t DisplayST7735::colorBlack = ST7735_BLACK;
uint16_t DisplayST7735::colorBlue = ST7735_BLUE;
uint16_t DisplayST7735::colorRed = ST7735_RED;
uint16_t DisplayST7735::colorGreen = ST7735_GREEN;

void DisplayST7735::init() {
    this->brightness = DEF_BRIGHTNESS;
    this->enabled = true;
    tft.initR(INITR_144GREENTAB);
    tft.fillScreen(ST7735_BLACK);
    invalidateState(this);

    ledcSetup(PWM_BACKLIGHT_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(PWM_BACKLIGHT_PIN, PWM_BACKLIGHT_CHANNEL);
    ledcWrite(PWM_BACKLIGHT_CHANNEL, DEF_BRIGHTNESS);
}

void DisplayST7735::update() {
    invalidateState(this);
    if(visible(this)) {
        tft.fillScreen(DisplayST7735::colorBlack);
    }
}

void DisplayST7735::setEnabled(bool enabled) {
    if(this->enabled == enabled) {
        return;
    }

    this->enabled = enabled;
    invalidateState(this);
}

bool DisplayST7735::isEnabled() {
    return this->enabled;
}

void DisplayST7735::setBrightness(byte level) {
    this->brightness = level;
    invalidateState(this);
}

byte DisplayST7735::getBrightness() {
    return this->brightness;
}

void DisplayST7735::text(const char *text, int size, uint16_t color, int x, int y) {
    tft.setTextSize(size);
    tft.setTextColor(color);
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void DisplayST7735::fill(uint16_t color) {
    tft.fillScreen(color);
}

void invalidateState(Display *display) {
    if(!visible(display)) {
        //analogWrite(TFT_LED, 0);
        return;
    }

    //analogWrite(TFT_LED, display->getBrightness());
}

bool visible(Display *display) {
    return display->isEnabled() && display->getBrightness() > 0;
}