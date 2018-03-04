#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>

typedef unsigned char byte;

class Display {
    public:
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void setEnabled(volatile bool enabled) = 0;
        virtual bool isEnabled();
        virtual void setBrightness(byte level) = 0;
        virtual byte getBrightness() = 0;
        ///draw api
        virtual void text(const char *text, int size, uint16_t color, int x = 0, int y = 0) = 0;
        virtual void fill(uint16_t color) = 0;
};

#endif //DISPLAY_H