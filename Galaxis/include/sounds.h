//
// Created by jmartens on 05.05.2024.
//

#ifndef GALAXIS_SOUNDS_H
#define GALAXIS_SOUNDS_H

#include "notes.h"
static int beep_1[] = {
        NOTE_B5, -8, REST, -8,
};

static int beep_2[] = {
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
};

static int beep_3[] = {
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
};

static int beep_4[] = {
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
        NOTE_B5, -8, REST, -8,
};

static int beep_0[] = {
        NOTE_C3, 1,
};

static int search[] = {
        NOTE_C3, -16,
        NOTE_A3, 4,
        NOTE_C3, -16,
        NOTE_A3, 4,
        NOTE_C3, -16,
        NOTE_A3, 4,
        NOTE_C3, -16,
        NOTE_A3, 4,
        NOTE_C3, -16,
        NOTE_A3, 4,
        NOTE_C3, -16,
        NOTE_A3, 4,
        REST, -4,
};

static int found[] = {
        NOTE_C3, 8,
        NOTE_F2, 12,
        NOTE_F2, 12,
        NOTE_C3, 8,
        NOTE_F2, 12,
        NOTE_F2, 12,
        NOTE_C3, 8,
        NOTE_F2, 12,
        NOTE_F2, 12,
        NOTE_C3, 8,
        NOTE_F2, 12,
        NOTE_F2, 12,
        NOTE_C3, 8,
        NOTE_F2, 12,
        NOTE_F2, 12,
};

static int idle[] = {
        NOTE_C3, 16,
        REST, 32,
        NOTE_C3, 16,
};

static int nope[] = {
        NOTE_A4, 16,
        REST, 32,
        NOTE_A4, 16,
        REST, 32,
        NOTE_A4, 16,
        REST, 32,
        NOTE_A4, 16,
};

#endif //GALAXIS_SOUNDS_H
