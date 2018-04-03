#ifndef window_h
#define window_h

#include "../widget/widget.h"

#define WIDGET_COUNT 4

class Window {
    Widget *widgets[WIDGET_COUNT];
    short last_added_widget;
    
    public:
        Window(): last_added_widget(0) {}

        void add_widget(Widget *widget) {
            if(last_added_widget < WIDGET_COUNT) {
                widgets[last_added_widget] = widget;
                ++last_added_widget;
            }
        }

        void update() { }
};

#endif /* window_h */
