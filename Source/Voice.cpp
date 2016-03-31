#include "Voice.h"



Voice::Voice() : _note(-1), _velocity(0), _isPlaying(false)
{

}


Voice::~Voice()
{

}


float Voice::nextSample()
{
    float sample = 0.f;
    if (_isPlaying) {
        // TODO : no filter
        sample = (float) _filter.filterValue((_oscillateur.nextSample() * _envelope.envelopeValue()));
    }
    return sample;
}


void Voice::releaseNote()
{
    if (_envelope.getState() != _envelope.idle) {
        _envelope.releaseNote();
    }
}


bool Voice::isPlaying()
{
    return _isPlaying;
}


void Voice::reset()
{
    _oscillateur.reset();
    _envelope.reset();
    _filter.reset();
}


void Voice::setNoteToPlay(int note)
{
    _oscillateur.setFrequency(note);
    _envelope.startAttack();
    _note = note;
    _isPlaying = true;
}


void Voice::setSampleRate(double sampleRate)
{
    Oscillateur::setSampleRate(sampleRate);
    Filter::setSampleRate(sampleRate);
    Envelope::setSampleRate(sampleRate);
}


void Voice::setAttackRate(double rate)
{
    _envelope.setAttackRate(rate);
}


void Voice::setDecayRate(double rate)
{
    _envelope.setDecayRate(rate);
}


void Voice::setReleaseRate(double rate)
{
    _envelope.setReleaseRate(rate);
}