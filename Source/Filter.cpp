#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Filter.h"



double Filter::_sampleRate = 44100.0;


Filter::Filter() : _cutoff(1000.0), _resonance(0.1), _filterType(noFilter)
{
    for (int i = 0; i < 2; ++i) {
        _prevIn[i] = 0.0;
        _prevOut[i] = 0.0;
        _a[i] = 0.0;
    }

    _b[0] = 1.0;
    _b[1] = 0.0;
    _b[2] = 0.0;
}


Filter::~Filter()
{

}


void Filter::reset()
{
    for (int i = 0; i < 2; ++i) {
        _prevIn[i] = 0.0;
        _prevOut[i] = 0.0;
        _a[i] = 0.0;
    }

    _b[0] = 1.0;
    _b[1] = 0.0;
    _b[2] = 0.0;
}


void Filter::setSampleRate(double sampleRate)
{
    _sampleRate = sampleRate;
    //updateCoef();
}


void Filter::setCutoff(double cutoff)
{
    /*if (_cutoff > _sampleRate / 2.0) {
        return;
    }*/
    _cutoff = std::fmin(std::fmax(cutoff, 1.0), (_sampleRate / 2.0) - 1.0);
    updateCoef();
}


void Filter::setResonance(double resonance)
{
    _resonance = resonance;
    updateCoef();
}


void Filter::setFilterType(int type)
{
    _filterType = type;
    if (_filterType != noFilter) {
        updateCoef();
    }
}


double Filter::filterValue(double value)
{
    double out;
    if (_filterType == noFilter) {
        out = value;
    } else {
        out = (_b[0] * value + _b[1] * _prevIn[0] + _b[2] * _prevIn[1]) - (_a[0] * _prevOut[0] + _a[1] * _prevOut[1]); // fmax(out, 0.99) + fmin(out, -0.99) ?
        _prevIn[1] = _prevIn[0];
        _prevIn[0] = value;
        _prevOut[1] = _prevOut[0];
        _prevOut[0] = out;
    }
    return out;
}


void Filter::updateCoef()
{
    // w = tan(PI * FréquenceFilter / FréquenceÉchantillonnage)
    double w = std::tan(M_PI * _cutoff / _sampleRate);
    double squareW = w * w;

    // n = 1 / (w² + w/Q + 1)
    double n = 1.0 / ((squareW) + (w / _resonance) + 1.0);

    switch (_filterType)
    {
        case lowPass:
            _b[0] = n * squareW;
            _b[1] = _b[0] * 2.0;
            _b[2] = _b[0];
            break;
        case highPass:
            _b[0] = n;
            _b[1] = -_b[0] * 2.0;
            _b[2] = _b[0];
            break;
        case bandPass:
            _b[0] = n * w / _resonance;
            _b[1] = 0.0;
            _b[2] = -_b[0];
            break;
        default:
            break;
    }

    _a[0] = 2.0 * n * (squareW - 1.0);
    _a[1] = n * (squareW - (w / _resonance) + 1.0);
}
