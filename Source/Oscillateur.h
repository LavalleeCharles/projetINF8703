#ifndef OSCILLATEUR_H
#define OSCILLATEUR_H

#include <vector>


enum waveTypes : int {sine=0, saw, square, triangle, NB_OF_WAVE_TYPES};


class Oscillateur
{
public:
    Oscillateur();
    ~Oscillateur();

    static void setSampleRate(double sampleRate);
    inline static void setWaveType(int waveType) { _waveType = waveType; }
    void setFrequency(int note);
    void reset();

    double nextSample();

private:
    void setPhaseStep();
    double polyBLEP(double t); // TODO

    double sineWave(double phase);
    double sawWave(double phase);
    double squareWave(double phase);
    double triangleWave(double phase);

private:
    static int _waveType;
    static double _sampleRate;
    double _frequency;
    double _phase;
    double _phaseStep;
    double _dt;
    double _t;
    double _PI;
    double _2_PI;
    const double _f0;

    double (Oscillateur::*_waveTypeTable[NB_OF_WAVE_TYPES])(double);
};

#endif // OSCILLATEUR_H
