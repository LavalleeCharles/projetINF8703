#ifndef VOICE_H
#define VOICE_H

#include "Oscillateur.h"
#include "Envelope.h"
// TODO : Filter


class Voice
{
public:
    Voice();
    ~Voice();

    float nextSample();
    void reset();

    void setNoteToPlay(int note);
    inline int getNote() const { return _note; }
    void releaseNote();
    bool isPlaying();
    inline void freeVoice() { _isPlaying = false; }
    inline bool isCycleFinished() { return _envelope.isCycleFinished(); }

    // Héritage?
    inline void setAttackLevel(double level) { _envelope.setAttackLevel(level); }
    inline void setDecayLevel(double level) { _envelope.setDecayLevel(level); }
    void setAttackRate(unsigned long long rate);
    void setDecayRate(unsigned long long rate);
    void setReleaseRate(unsigned long long rate);

private:
    Oscillateur<float> _oscillateur;
    Envelope _envelope;
    // Filter _filter

    int _note;
    int _velocity;
    bool _isPlaying;
};



#endif  // VOICE_H
