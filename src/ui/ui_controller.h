#ifndef ui_controller_h
#define ui_controller_h

#include "window/window.h"

#define WINDOW_COUNT 4

class UIController {

    private:
        Window *windows[WINDOW_COUNT];
        short current_window_index;
        short window_count;

    public:
        UIController(): current_window_index(0), window_count(WINDOW_COUNT) { }

    void update() {
        Window *current = current_window();
        assert(current != NULL);
        
        current->update();
        printf("window manager update. screens: %d\n", window_count);
    }

    Window *current_window() {
        windows[current_window_index];
    }

    void switch_window (short window_num) {
        assert(window_num >= 0);
        assert(window_count > window_num);
    
        if(current_window_index != window_num) {
            printf("window manager switch to window: %d\n", window_num);
            Window *window = windows[window_num];
            
            current_window_index = window_num;
            window->update();
        } else {
            printf("cant switch to window: %d\n", window_num);
        }
    }
};

#endif //ui_controller_h
