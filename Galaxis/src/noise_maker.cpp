//
// Created by jmartens on 05.05.2024.
//

#include "noise_maker.h"
#include "settings.h"
#include "Arduino.h"
#include "tone.h"

//void NoiseMaker::playMelody(int melody[], int notesCount) {
//#ifdef SILENT
//    return;
//#else
//    for (int thisNote = 0; thisNote < notesCount * 2; thisNote += 2) {
//        uint16_t divider = melody[thisNote + 1];
//        int8_t noteDuration;
//        if (divider > 0) {
//            noteDuration = (_wholeNote) / divider;
//        } else if (divider < 0) {
//            noteDuration = (_wholeNote) / abs(divider);
//            noteDuration *= 1.5;
//        }
//
//        tone(PIN_TONE_OUTPUT, melody[thisNote], noteDuration * 0.9);
//        //delay(noteDuration);
//        noTone(PIN_TONE_OUTPUT);
//    }
//#endif
//}

void NoiseMaker::appendTones(int melody[], int notesCount) {
#ifdef SILENT
    return;
#else
    for (int thisNote = 0; thisNote < notesCount * 2; thisNote += 2) {
        int divider = melody[thisNote + 1];
        int noteDuration = (_wholeNote) / abs(divider);
        if (divider < 0) {
            noteDuration *= 1.5;
        }

        _tones.push(std::make_unique<Tone>(Tone({static_cast<uint16_t>(melody[thisNote]), noteDuration})));
    }
#endif
}

void NoiseMaker::loop() {
#ifdef SILENT
    return;
#else
    if (isPlaying())
        return;

    if (!_tones.empty()) {
        playNextTone();
        return;
    }

    _playUntil = 0;
    _currentTone = nullptr;
    noTone(PIN_TONE_OUTPUT);
#endif
}

void NoiseMaker::playNextTone() {
    _currentTone = std::move(_tones.front());
    _tones.pop();
    _playUntil = millis() + _currentTone->duration;
    tone(PIN_TONE_OUTPUT, _currentTone->pitch);
}

bool NoiseMaker::isPlaying() const { return _playUntil > millis(); }

void NoiseMaker::playWinner() {
#ifdef SILENT
    return;
#else
    noTone(PIN_TONE_OUTPUT);

    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 100; i++) {
            tone(PIN_TONE_OUTPUT, 475 + i * 5, 5);
        }
        for (int i = 100; i > 0; i--) {
            tone(PIN_TONE_OUTPUT, 475 + i * 5, 5);
        }
    }

    noTone(PIN_TONE_OUTPUT);
#endif
}
