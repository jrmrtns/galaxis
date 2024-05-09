//
// Created by jmartens on 05.05.2024.
//

#ifndef GALAXIS_NOISE_MAKER_H
#define GALAXIS_NOISE_MAKER_H

#include <cstdint>
#include <queue>
#include <memory>
#include "tone.h"

class NoiseMaker {
public:
    void appendTones(int melody[], int notesCount);

    void playWinner();

    void loop();

private:
    int _tempo = 115;
    int _wholeNote = (60000 * 4) / _tempo;
    std::queue<std::unique_ptr<Tone>> _tones;
    std::unique_ptr<Tone> _currentTone = nullptr;
    uint64_t _playUntil = 0;

    bool isPlaying() const;

    void playNextTone();

    void stopTone();
};


#endif //GALAXIS_NOISE_MAKER_H
