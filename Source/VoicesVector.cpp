#include "VoicesVector.h"



VoicesVector::VoicesVector()
{

}


VoicesVector::~VoicesVector()
{

}


void VoicesVector::setNumberOfVoices(std::size_t nbOfVoices)
{
	// TODO : ...
    _size = nbOfVoices;
    for (std::size_t i = 0; i < _size; ++i) {
        _voices.push_back(new Voice);
    }
}


std::size_t VoicesVector::size() const
{
    return _size;
}


void VoicesVector::noteOn(int note, float velocity)
{
    Voice* newVoice = getFreeVoice();
    if (newVoice != nullptr) {
        newVoice->reset();
        newVoice->setNoteToPlay(note);
        // newVoice->setVelocity(velocity);
        // ...
    }
}


void VoicesVector::noteOff(int note, float velocity)
{
    for (std::size_t i = 0; i < _size; ++i) {
        if (_voices[i]->isPlaying() && note == _voices[i]->getNote()) {
            _voices[i]->releaseNote();
        }

        // TODO : implement below with signals...
        if (_voices[i]->isCycleFinished()) {
            _voices[i]->freeVoice();
        }
    }
}


void VoicesVector::pitchWheelOn(double pitchWheelValue)
{
    for (std::size_t i = 0; i < _size; ++i) {
        if (_voices[i]->isPlaying()) {
            _voices[i]->setPitchModulation(pitchWheelValue);
        }
    }
}


Voice* VoicesVector::getFreeVoice()
{
    for (std::size_t i = 0; i < _size; ++i) {
        if (!_voices[i]->isPlaying()) {
            return _voices[i];
        }

        // TODO : implement below with signals...
        if (_voices[i]->isCycleFinished()) {
            _voices[i]->freeVoice();
        }
    }
    return nullptr;
}


float VoicesVector::nextSample()
{
    float sample = 0.f;
    for (std::size_t i = 0; i < _size; ++i) {
        sample += _voices[i]->nextSample();
    }
    return sample;
}


void VoicesVector::updateEnvelope(double value, Envelope::envelopeParamIndex paramId)
{
    // TODO : tableau de fonction?
    for (std::size_t i = 0; i < _size; ++i) {
        switch (paramId) {
            case Envelope::envelopeParamIndex::attackLevel:
                _voices[i]->setAttackLevel(value);
                break;
            case Envelope::envelopeParamIndex::decayLevel:
                _voices[i]->setDecayLevel(value);
                break;
            case Envelope::envelopeParamIndex::attackRate:
                _voices[i]->setAttackRate(value);
                break;
            case Envelope::envelopeParamIndex::decayRate:
                _voices[i]->setDecayRate(value);
                break;
            case Envelope::envelopeParamIndex::releaseRate:
                _voices[i]->setReleaseRate(value);
                break;
            default:
                break;
        }
    }
}


