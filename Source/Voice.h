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
    void setNoteToPlay(int note, int velocity);
    void releaseNote();
    bool isPlaying();
    void freeVoice();
    inline bool isCycleFinished() { return _envelope.isCycleFinished(); }
    inline int getNote() const { return _note; }

    // ------------------- Parameters -------------------
    static void setSampleRate(double sampleRate);

    // Oscillator parameters
    void setOscillatorWaveType(int waveType);
    void setPitchModulation(double pitchModulationValue);

    // Envelope parameters
    inline void setAttackLevel(double level) { _envelope.setAttackLevel(level); }
    inline void setDecayLevel(double level) { _envelope.setDecayLevel(level); }
    void setAttackRate(double rate);
    void setDecayRate(double rate);
    void setReleaseRate(double rate);

    // Filter parameters
    void setFilterCutoff(double cutoff);
    inline void setFilterType(int type) { _filter.setFilterType(type); }
    inline void setFilterResonance(double resonance) { _filter.setResonance(resonance); }

    // LFO
    void setLfoWaveType(int waveType);
    void setLfoFrequency(double freq);
    void setLfoAmount(double lfoAmount);
    // --------------------------------------------------

private:
    Oscillateur _oscillateur;
    Envelope _envelope;
    Filter _filter;
    double _filterCutoffValue;
    Oscillateur _lfo;
    double _lfoAmount;

    int _note;
    int _velocity;
    bool _isPlaying;
    const double _f0;
};



#endif  // VOICE_H
