#ifndef widget_h
#define widget_h

#include "../core.h"

class Widget {
    TPoint start;
    TSize size;
    int color;

    public:
        void update() {
            printf("widget update, %p: x[%d] y[%d] w[%d] h[%d]\n",
                (void*) this,
                start.x,
                start.y,
                size.width,
                size.height);
        }
};

#endif /* widget_h */
