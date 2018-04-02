#include "dev/display/display_ST7735.h"

class DevController {
    private:
        Display *display;

    public:
        DevController() {
            display = new DisplayST7735();
        }

        void init() {
            display->init();
        }

        Display *getDisplay() {
            return display;
        }
};