#include "display_ST7735.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

#define TFT_SCLK 13
#define TFT_MOSI 11

#define TFT_LED 6

#define DEF_BRIGHTNESS 30

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

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
    pinMode(TFT_LED, OUTPUT);
    invalidateState(this);
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
        analogWrite(TFT_LED, 0);
        return;
    }

    analogWrite(TFT_LED, display->getBrightness());
}

bool visible(Display *display) {
    return display->isEnabled() && display->getBrightness() > 0;
}