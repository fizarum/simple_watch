#include "dev/display/display_ST7735.h"
#include "dev/rtc/rtc_DS1307.h"

class DevController {
    private:
        Display *display;
        RtcDS1307 *rtc;

    public:
        DevController() {
            display = new DisplayST7735();
            rtc = new RtcDS1307(); 
        }

        void init() {
            display->init();
            rtc->init();
        }

        // void update() {
        //     display->update();
        //     // rtc->update();
        // }

        Display *getDisplay() {
            return display;
        }

        RtcDS1307 *getRtc() {
            return rtc;
        }
};