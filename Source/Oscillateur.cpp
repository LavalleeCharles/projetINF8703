#include <cmath>
#include <typeinfo>

#include "Oscillateur.h"



double Oscillateur::_sampleRate = 48000.0;
int Oscillateur::_waveType = 0;


Oscillateur::Oscillateur() : _frequency(440.0), _phase(0.0), _f0(440.0)
{
    setPhaseStep();
    _t = 0.0;

    _waveTypeTable[sine] = &Oscillateur::sineWave;
    _waveTypeTable[saw] = &Oscillateur::sawWave;
    _waveTypeTable[square] = &Oscillateur::squareWave;
    _waveTypeTable[triangle] = &Oscillateur::triangleWave;

    _PI = M_PI;
    _2_PI = M_2_PI;
}



Oscillateur::~Oscillateur()
{

}



void Oscillateur::setSampleRate(double sampleRate)
{
    _sampleRate = sampleRate;
    //setPhaseStep();
    // TODO : updater le _phaseStep pour tout les oscillateurs???
}



void Oscillateur::setFrequency(int note)
{
    _frequency = _f0 * std::pow(2.0, (note - 81) / 12.0);
    setPhaseStep();
}



void Oscillateur::setPhaseStep()
{
    _dt = _frequency / _sampleRate; // pour polyBLEP
    _phaseStep = _2_PI * _dt;
}


void Oscillateur::reset()
{
    _phase = 0.0;
}


double Oscillateur::nextSample()
{
    double value = (this->*_waveTypeTable[_waveType])(_phase);
    _phase += _phaseStep;
    while (_phase >= _2_PI) {
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
    return 1.0 - (2 * phase / _2_PI);
}



double Oscillateur::squareWave(double phase)
{
    if (phase <= _PI) {
        return 1.0;
    } else {
        return -1.0;
    }
}



double Oscillateur::triangleWave(double phase)
{
    double tmp = -1.0 + (2 * phase / _2_PI);
    return 2.0 * (std::fabs(tmp) - 0.5);
}
