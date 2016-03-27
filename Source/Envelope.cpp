#include <cmath>
#include "Envelope.h"



Envelope::Envelope()
        : _minLevel(0.0001), _attackLevel(1.0), _decayLevel(0.8), _finishedRelease(false)
{
    reset();

    setAttackRate(1);
    setDecayRate(1);
    setReleaseRate(1);
}


Envelope::~Envelope()
{

}


void Envelope::reset()
{
    _state = idle;
    _envValue = _minLevel;
}


// Tiré de: www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
double Envelope::multiplier(double startLevel, double endLevel, unsigned long long lengthInSamples)
{
    return 1.0 + (std::log(endLevel) - std::log(startLevel)) / (lengthInSamples);
}


void Envelope::setAttackLevel(double level)
{
    _attackLevel = level;
    _attackMultiplier = multiplier(_minLevel, _attackLevel, _attackLength);
}


void Envelope::setDecayLevel(double level)
{
    _decayLevel = level;
    _decayMultiplier = multiplier(1.0, _decayLevel, _decayLength);
}


void Envelope::setAttackRate(unsigned long long rate)
{
    _attackLength = rate;
    _attackMultiplier = multiplier(_minLevel, _attackLevel, _attackLength);
}


void Envelope::setDecayRate(unsigned long long rate)
{
    _decayLength = rate;
    _decayMultiplier = multiplier(1.0, _decayLevel, _decayLength);
}


void Envelope::setReleaseRate(unsigned long long rate)
{
    _releaseLength = rate;
    _releaseMultiplier = multiplier(_decayLevel, _minLevel, _releaseLength);
}


void Envelope::startAttack()
{
    _state = attack;
    _finishedRelease = false;
}


void Envelope::releaseNote()
{
    _state = release;
}


int Envelope::getState()
{
    return _state;
}


double Envelope::envelopeValue()
{
    switch (_state)
    {
        case idle:
        {
            break;
        }
        case attack:
        {
            _envValue *= _attackMultiplier;
            if (_envValue >= 1.0) {
                _envValue = 1.0;
                _state = decay;
            }
            break;
        }
        case decay:
        {
            _envValue *= _decayMultiplier;
            if (_envValue <= _decayLevel) {
                _envValue = _decayLevel;
                _state = sustain;
            }
            break;
        }
        case sustain:
        {
            break;
        }
        case release:
        {
            _envValue *= _releaseMultiplier;
            if (_envValue <= _minLevel) {
                _envValue = _minLevel;
                _state = idle;

                _finishedRelease = true; // the Voice can be set free (TODO: should probably be implemented with signals)
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return _envValue;
}





