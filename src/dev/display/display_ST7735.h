#ifndef DISPLAY_ST7735_H
#define DISPLAY_ST7735_H

#include "display.h"

class DisplayST7735 : public Display {
    private:
        byte brightness;
        bool enabled;

    public:
        static uint16_t colorBlack;
        static uint16_t colorBlue;
        static uint16_t colorRed;
        static uint16_t colorGreen;

        void init();
        void update();
        void setEnabled(bool enabled);
        bool isEnabled();
        void setBrightness(byte level);
        byte getBrightness();

        void text(const char *text, int size, uint16_t color, int x = 0, int y = 0);
        void fill(uint16_t color);
};

#endif //DISPLAY_ST7735_H