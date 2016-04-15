#include <cmath>
#include "Voice.h"



Voice::Voice() : _note(-1), _velocity(0), _f0(440.0), _isPlaying(false), _lfoAmount(0.0)
{

}


Voice::~Voice()
{

}


float Voice::nextSample()
{
    float sample = 0.f;
    if (_isPlaying) {
        _filter.setCutoff(_filter.getCutoff() + (_lfo.nextSample() * _lfoAmount));
        sample = (float) _filter.filterValue(_oscillateur.nextSample() * _envelope.envelopeValue() * (_velocity / 127.0));
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
    _lfo.reset();
    _filter.reset();
}


void Voice::setNoteToPlay(int note, int velocity)
{
    _oscillateur.setFrequency(_f0 * std::pow(2.0, (note - 81.0) / 12.0));
    _envelope.startAttack();
    _filter.updateCoef();
    _note = note;
    _velocity = velocity;
    _isPlaying = true;
}


void Voice::setSampleRate(double sampleRate)
{
    Oscillateur::setSampleRate(sampleRate);
    Filter::setSampleRate(sampleRate);
    Envelope::setSampleRate(sampleRate);
}


void Voice::setOscillatorWaveType(int waveType)
{
    _oscillateur.setWaveType(waveType);
}


void Voice::setPitchModulation(double pitchModulationValue)
{
    _oscillateur.setPitchModulation(pitchModulationValue);
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


void Voice::setLfoWaveType(int waveType)
{
    _lfo.setWaveType(waveType);
}


void Voice::setLfoFrequency(double freq)
{
    _lfo.setFrequency(freq);
}


void Voice::setLfoAmount(double lfoAmount)
{
    _lfoAmount = lfoAmount;
}


void Voice::freeVoice()
{
    _isPlaying = false;
    reset();
}