//
// Created by jmartens on 04.11.2023.
//

#ifndef GALAXIS_VIEW_H
#define GALAXIS_VIEW_H

#include "screen.h"

class IView {
public:
    virtual Screen loop() = 0;

    virtual void show() = 0;
};

#endif //GALAXIS_VIEW_H
