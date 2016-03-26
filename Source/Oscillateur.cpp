#include <cmath>

#include "Oscillateur.h"


const float f_PI = 3.1415927f;
const float f_2_PI = (2.f * f_PI);

Oscillateur::Oscillateur() : _waveType(0), _sampleRate(48000.f), _frequency(440.f), _phase(0.f), _f0(440.f)
{
    setPhaseStep();

    _waveTypeTable[sine] = &Oscillateur::sineWave;
    _waveTypeTable[saw] = &Oscillateur::sawWave;
    _waveTypeTable[square] = &Oscillateur::squareWave;
    _waveTypeTable[triangle] = &Oscillateur::triangleWave;
}


Oscillateur::~Oscillateur()
{

}


void Oscillateur::setSampleRate(float sampleRate)
{
    _sampleRate = sampleRate;
    setPhaseStep();
}


void Oscillateur::setFrequency(int note)
{
    _frequency = _f0 * std::pow(2.f, (note - 69) / 12.f);;
    setPhaseStep();
}


void Oscillateur::setPhaseStep()
{
    _phaseStep = 2 * f_PI * _frequency / _sampleRate;
}


void Oscillateur::setWaveType(int waveType)
{
    _waveType = waveType;
}


void Oscillateur::play(float* buffer, int nbFrames)
{
    for (int i = 0; i < nbFrames; ++i) {
        buffer[i] = (this->*_waveTypeTable[_waveType])(_phase);
        _phase += _phaseStep;
        if (_phase >= f_2_PI) {
            _phase -= f_2_PI;
        }
    }
}


float Oscillateur::sineWave(float phase)
{
    return sinf(phase);
}


float Oscillateur::sawWave(float phase)
{
    return 1.f - (2.f * phase / f_2_PI);
}


float Oscillateur::squareWave(float phase)
{
    if (phase <= f_PI) {
        return 1.f;
    } else {
        return -1.f;
    }
}

float Oscillateur::triangleWave(float phase)
{
    /*
    if (phase <= f_PI) {
        return -1.f + (2.f * phase / f_PI);
    } else {
        return 1.f - (2.f * phase / f_PI);
    }*/
    float tmp = -1.f + (2.f * phase / f_2_PI);
    return 2.f * (fabsf(tmp) - 0.5f);

}