#include <cmath>
#include <typeinfo>

#include "Oscillateur.h"


template <typename T>
T Oscillateur<T>::_sampleRate = T(48000.);
template <typename T>
int Oscillateur<T>::_waveType = 0;


template <typename T>
Oscillateur<T>::Oscillateur() : _frequency(T(440.)), _phase(T(0.)), _f0(T(440.))
{
    setPhaseStep();
    _t = T(0.);

    _waveTypeTable[sine] = &Oscillateur<T>::sineWave;
    _waveTypeTable[saw] = &Oscillateur<T>::sawWave;
    _waveTypeTable[square] = &Oscillateur<T>::squareWave;
    _waveTypeTable[triangle] = &Oscillateur<T>::triangleWave;

    if (typeid(T) == typeid(float)) {
        _PI = 3.1415927f;
    } else {
        _PI = M_PI;
    }
    _2_PI = 2 * _PI;
}


template <typename T>
Oscillateur<T>::~Oscillateur()
{

}


template <typename T>
void Oscillateur<T>::setSampleRate(T sampleRate)
{
    _sampleRate = sampleRate;
    //setPhaseStep();
}


template <typename T>
void Oscillateur<T>::setFrequency(int note)
{
    _frequency = _f0 * std::pow(T(2.), (note - 81) / T(12.));
    setPhaseStep();
}


template <typename T>
void Oscillateur<T>::setPhaseStep()
{
    _dt = _frequency / _sampleRate; // pour polyBLEP
    _phaseStep = _2_PI * _dt;
}


template <typename T>
void Oscillateur<T>::setWaveType(int waveType)
{
    _waveType = waveType;
}


template <typename T>
void Oscillateur<T>::reset()
{
    _phase = T(0.);
}


template <typename T>
T Oscillateur<T>::nextSample()
{
    T value = (this->*_waveTypeTable[_waveType])(_phase);
    _phase += _phaseStep;
    while (_phase >= _2_PI) {
        _phase -= _2_PI;
    }
    return value;
}


// Tiré de: http://www.kvraudio.com/forum/viewtopic.php?t=375517
template <typename T>
T Oscillateur<T>::polyBLEP(T t)
{
    // 0 <= t < 1
    if (t < _dt) {
        t /= _dt;
        // 2 * (t - t^2/2 - 0.5)
        return (t + t) - (t * t) - T(1.);
    // -1 < t < 0
    } else if (t > 1. - _dt) {
        t = (t - T(1.)) / _dt;
        // 2 * (t^2/2 + t + 0.5)
        return (t * t) + (t + t) + T(1.);
    // 0 otherwise
    } else {
        return T(0.);
    }
}


template <typename T>
T Oscillateur<T>::sineWave(T phase)
{
    return std::sin(phase);
}


template <typename T>
T Oscillateur<T>::sawWave(T phase)
{
    return T(1.) - (2 * phase / _2_PI);
}


template <typename T>
T Oscillateur<T>::squareWave(T phase)
{
    if (phase <= _PI) {
        return T(1.);
    } else {
        return T(-1.);
    }
}


template <typename T>
T Oscillateur<T>::triangleWave(T phase)
{
    T tmp = T(-1.) + (2 * phase / _2_PI);
    return T(2.) * (std::fabs(tmp) - T(0.5));
}


// Explicit template instantiation
template class Oscillateur<float>;
template class Oscillateur<double>;