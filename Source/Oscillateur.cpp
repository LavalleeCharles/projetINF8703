#define _USE_MATH_DEFINES
#include <cmath>
#include <typeinfo>

#include "Oscillateur.h"


double Oscillateur::_sampleRate = 44100.0;

Oscillateur::Oscillateur() : _frequency(440.0), _phase(0.0), _waveType(0), _pitchModulation(1.0)
{
    setPhaseStep();
    _t = 0.0;

    _waveTypeTable[sine] = &Oscillateur::sineWave;
    _waveTypeTable[saw] = &Oscillateur::sawWave;
    _waveTypeTable[square] = &Oscillateur::squareWave;
    _waveTypeTable[triangle] = &Oscillateur::triangleWave;

    _PI = M_PI;
    _2_PI = M_PI * 2.0;
}


Oscillateur::~Oscillateur()
{

}


void Oscillateur::setSampleRate(double sampleRate)
{
    _sampleRate = sampleRate;
}


void Oscillateur::setWaveType(int waveType)
{
    _waveType = waveType;
}


void Oscillateur::setFrequency(double freq)
{
    _frequency = freq;
    setPhaseStep();
}


void Oscillateur::setPitchModulation(double pitchModulation)
{
    _pitchModulation = std::pow(2.0, (pitchModulation - 8192) / (49152)); // 49152 = 4096 * 12
    setPhaseStep();
}


void Oscillateur::setPhaseStep()
{
    _dt = _pitchModulation * _frequency / _sampleRate; // pour polyBLEP
	_phaseStep = _pitchModulation * _frequency * _2_PI / _sampleRate;
}


void Oscillateur::reset()
{
    _phase = 0.0;
    _pitchModulation = 1.0;
    //_phaseStep = 0.0;
}


double Oscillateur::nextSample()
{
    double value = (this->*_waveTypeTable[_waveType])(_phase);
    _phase += _phaseStep;
    if (_phase >= _2_PI) {
        _phase -= _2_PI;
    }
    return value;
}


// Tiré de: http://www.kvraudio.com/forum/viewtopic.php?t=375517
double Oscillateur::polyBLEP(double t)
{
    // 0 <= t < 1
    if (t < _dt) {
        t /= _dt;
        // 2 * (t - t^2/2 - 0.5)
        return (t + t) - (t * t) - 1.0;
    // -1 < t < 0
    } else if (t > 1. - _dt) {
        t = (t - 1.0) / _dt;
        // 2 * (t^2/2 + t + 0.5)
        return (t * t) + (t + t) + 1.0;
    // 0 otherwise
    } else {
        return 0.0;
    }
}


double Oscillateur::sineWave(double phase)
{
    return std::sin(phase);
}


double Oscillateur::sawWave(double phase)
{
    return 1.0 - (2.0 * phase / _2_PI);
}


double Oscillateur::squareWave(double phase)
{
    return phase <= _PI ? 1.0 : -1.0;
}


double Oscillateur::triangleWave(double phase)
{
    double tmp = -1.0 + (2 * phase / _2_PI);
    return 2.0 * (std::fabs(tmp) - 0.5);
}
