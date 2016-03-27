#ifndef VOICESVECTOR_H
#define VOICESVECTOR_H


#include <vector>

#include "Voice.h"


class VoicesVector
{
public:
    VoicesVector();
    ~VoicesVector();

    Voice* operator[](std::size_t i) { return _voices[i]; }

    void setNumberOfVoices(std::size_t nbOfVoices);
    std::size_t size() const;

    void noteOn(int note, float velocity);
    void noteOff(int note, float velocity);

    float nextSample();

private:
    Voice* getNextVoice();

private:
    std::vector<Voice*> _voices;

    std::size_t _size;
};



#endif  // VOICESVECTOR_H
