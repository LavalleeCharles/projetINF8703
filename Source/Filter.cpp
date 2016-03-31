#define _USE_MATH_DEFINES
#include <cmath>
#include "Filter.h"



double Filter::_sampleRate = 44100.0;
double Filter::_cutoff = 1000.0;
double Filter::_resonance = 0.1;
double Filter::_b[3] = { 0.5, 0.0, 0.0 };
double Filter::_a[2] = { 0.0, 0.0 };
int Filter::_filterType = lowPass;


Filter::Filter()
{
    for (int i = 0; i < 2; ++i) {
        _prevIn[i] = 0.0;
        _prevOut[i] = 0.0;
    }
}


Filter::~Filter()
{

}


void Filter::reset()
{
    for (int i = 0; i < 2; ++i) {
        _prevIn[i] = 0.0;
        _prevOut[i] = 0.0;
    }
}


void Filter::setSampleRate(double sampleRate)
{
    _sampleRate = sampleRate;
    updateCoef();
}


void Filter::setCutoff(double cutoff)
{
    if (_cutoff > _sampleRate / 2.0) {
        return;
    }
    _cutoff = cutoff;
    updateCoef();
}


void Filter::setResonance(double resonance)
{
    if (resonance >= 1.0) {
        return;
    }
    _resonance = resonance;
    updateCoef();
}


void Filter::setFilterType(int type)
{
    _filterType = type;
    updateCoef();
}


double Filter::filterValue(double value)
{
    double out = (_b[0] * value + _b[1] * _prevIn[0] + _b[2] * _prevIn[1]) - (_a[0] * _prevOut[0] + _a[1] * _prevOut[1]);

    _prevOut[1] = _prevOut[0];
    _prevOut[0] = out;
    _prevIn[1] = _prevIn[0];
    _prevIn[0] = value;

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

    _a[0] = 2.0 * n * (squareW - 1);
    _a[1] = n * (squareW - (w / _resonance) + 1.0);
}
