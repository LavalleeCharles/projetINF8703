#ifndef VOICE_H
#define VOICE_H

#include "Oscillateur.h"
#include "Envelope.h"
#include "Filter.h"


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

    static void setSampleRate(double sampleRate);
    inline static void setWaveType(int waveType) { Oscillateur::setWaveType(waveType); }

    inline static void setFilterType(int type) { Filter::setFilterType(type); }
    inline static void setCutoff(double cutoff) { Filter::setCutoff(cutoff); }
    inline static void setResonance(double resonance) { Filter::setResonance(resonance); }

private:
    Oscillateur _oscillateur;
    Envelope _envelope;
    Filter _filter;

    int _note;
    int _velocity;
    bool _isPlaying;
};



#endif  // VOICE_H
