//
//  button.h
//  argui
//
//  Created by Mykhailo Zhyliakov on 12/01/2018.
//  Copyright © 2018 Mykhailo Zhyliakov. All rights reserved.
//

#ifndef button_h
#define button_h

#include <assert.h>
#include "widget.h"

typedef struct Button {
    void (*update) (struct Button *self);
    void (*on_pressed) (struct Button *self, void (*callback)(void));
    Widget *parent;
} Button;

void button_update(Button *self);
void button_pressed(Button *self, void (*callback)(void));

Button *button_create(void) {
    Button *button = malloc(sizeof(Button));
    button->parent = widget_create();
    button->update = button_update;
    button->on_pressed = button_pressed;
    return button;
}

void button_update(Button *self) {
    assert(self != NULL);
    assert(self->parent != NULL);
    printf("update button: %p\n", (void*)self);
}

void button_pressed(Button *self, void (*callback)(void)) {
    (*callback)();
}

#endif /* button_h */
