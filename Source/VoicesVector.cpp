#include "VoicesVector.h"



VoicesVector::VoicesVector()
{

}


VoicesVector::~VoicesVector()
{

}


void VoicesVector::setNumberOfVoices(std::size_t nbOfVoices)
{
    _size = nbOfVoices;
    for (int i = 0; i < _size; ++i) {
        _voices.push_back(new Voice);
    }
}


std::size_t VoicesVector::size() const
{
    return _size;
}


void VoicesVector::noteOn(int note, float velocity)
{
    Voice* newVoice = getNextVoice();
    if (newVoice != nullptr) {
        newVoice->reset();
        newVoice->setNoteToPlay(note);
        // newVoice->setVelocity(velocity);
        // ...
    }
}


void VoicesVector::noteOff(int note, float velocity)
{
    for (int i = 0; i < _size; ++i) {
        if (_voices[i]->isPlaying() && note == _voices[i]->getNote()) {
            _voices[i]->releaseNote();
        }

        // TODO : implement below with signals...
        if (_voices[i]->isCycleFinished()) {
            _voices[i]->freeVoice();
        }
    }
}


Voice* VoicesVector::getNextVoice()
{
    for (int i = 0; i < _size; ++i) {
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
    for (int i = 0; i < _size; ++i) {
        sample += _voices[i]->nextSample();
    }
    return sample;
}






