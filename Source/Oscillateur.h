#ifndef OSCILLATEUR_H
#define OSCILLATEUR_H

#include <vector>


enum waveTypes : int {sine=0, saw, square, triangle, NB_OF_WAVE_TYPES};

template <typename T>
class Oscillateur
{
public:
    Oscillateur();
    ~Oscillateur();

    static void setSampleRate(T sampleRate);
    static void setWaveType(int waveType);
    void setFrequency(int note);
    void reset();

    T nextSample();

private:
    void setPhaseStep();
    T polyBLEP(T t); // TODO

    T sineWave(T phase);
    T sawWave(T phase);
    T squareWave(T phase);
    T triangleWave(T phase);

private:
    static int _waveType;
    static T _sampleRate;
    T _frequency;
    T _phase;
    T _phaseStep;
    T _dt;
    T _t;
    T _PI;
    T _2_PI;
    const T _f0;

    T (Oscillateur::*_waveTypeTable[NB_OF_WAVE_TYPES])(T);
};

#endif // OSCILLATEUR_H
