//
// Created by jmartens on 05.05.2024.
//

#include "noise_maker.h"
#include "settings.h"
#include "Arduino.h"
#include "tone.h"
#include "sounds.h"

extern bool playSound;
extern bool playIdleSound;

void NoiseMaker::appendTones(int melody[], int notesCount) {
    if (!playSound) return;
    for (int thisNote = 0; thisNote < notesCount * 2; thisNote += 2) {
        int divider = melody[thisNote + 1];
        int noteDuration = (_wholeNote) / abs(divider);
        if (divider < 0) {
            noteDuration *= 1.5;
        }

        _tones.push(std::make_unique<Tone>(Tone({static_cast<uint16_t>(melody[thisNote]), noteDuration})));
    }
}

void NoiseMaker::loop() {
    if (!playSound) return;

    if (isPlaying())
        return;

    if (_tones.empty()) {
        stopTone();
        return;
    }

    playNextTone();
}

void NoiseMaker::stopTone() {
    _playUntil = 0;
    _currentTone = nullptr;
    noTone(PIN_TONE_OUTPUT);
}

void NoiseMaker::playNextTone() {
    _currentTone = std::move(_tones.front());
    _tones.pop();
    _playUntil = millis() + _currentTone->duration;
    tone(PIN_TONE_OUTPUT, _currentTone->pitch);
}

bool NoiseMaker::isPlaying() const { return _playUntil > millis(); }

void NoiseMaker::playWinner() {
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 25; i++) {
            _tones.push(std::make_unique<Tone>(Tone{440 + i * 30, 20}));
        }
        for (int i = 25; i > 0; i--) {
            _tones.push(std::make_unique<Tone>(Tone{440 + i * 30, 20}));
        }
    }
}

void NoiseMaker::playBeep(uint8_t count) {
    if (count == 0)
        appendTones(beep_0, 1);
    if (count == 1)
        appendTones(beep_1, 2);
    if (count == 2)
        appendTones(beep_2, 4);
    if (count == 3)
        appendTones(beep_3, 6);
    if (count == 4)
        appendTones(beep_4, 8);
    if (count == 0xfe)
        appendTones(nope, 7);
}

void NoiseMaker::playFound() {
    appendTones(found, 15);
}

void NoiseMaker::playIdle() {
    if (playIdleSound)
        appendTones(idle, 3);
}

void NoiseMaker::playSearch() {
    appendTones(search, 13);
}
