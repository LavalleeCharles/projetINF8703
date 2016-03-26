#ifndef OSCILLATEUR_H
#define OSCILLATEUR_H

#include <vector>


enum waveTypes : int {sine=0, saw, square, triangle, NB_OF_WAVE_TYPES};

class Oscillateur
{
public:
    Oscillateur();
    ~Oscillateur();

    void setSampleRate(float sampleRate);
    void setFrequency(int note);
    void setWaveType(int waveType);

    void play(float* buffer, int nbFrames);

private:
    void setPhaseStep();

    float sineWave(float phase);
    float sawWave(float phase);
    float squareWave(float phase);
    float triangleWave(float phase);

private:
    int _waveType;
    float _sampleRate;
    float _frequency;
    float _phase;
    float _phaseStep;
    const float _f0;

    float (Oscillateur::*_waveTypeTable[NB_OF_WAVE_TYPES])(float);
};

#endif // OSCILLATEUR_H
