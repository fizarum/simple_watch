//
//  label.h
//  argui
//
//  Created by Mykhailo Zhyliakov on 10/01/2018.
//  Copyright © 2018 Mykhailo Zhyliakov. All rights reserved.
//

#ifndef label_h
#define label_h

#include <stdlib.h>
#include <assert.h>

#include "widget.h"

typedef struct Label {
    void (*update) (struct Label *self);
    Widget *parent;
} Label;

void label_update(Label *self) {
    assert(self != NULL);
    assert(self->parent != NULL);
    //todo: additional update label logic here
    printf("update label: %p\n", (void *) self);
}

Label *label_create(void) {
    Label *label = malloc(sizeof(Label));
    label->parent = widget_create();
    label->update = label_update;
    return label;
}

#endif /* label_h */
