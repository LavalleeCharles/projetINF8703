#ifndef VOICESVECTOR_H
#define VOICESVECTOR_H


#include <vector>

#include "Voice.h"


class VoicesVector
{
public:
    VoicesVector();
    ~VoicesVector();

    void setNumberOfVoices(std::size_t nbOfVoices);
    std::size_t size() const;

    void noteOn(int note, float velocity);
    void noteOff(int note, float velocity);
	void pitchWheelOn(double pitchWheelValue);

    float nextSample();

	void updateEnvelope(double value, Envelope::envelopeParamIndex paramId);
	//void updateFilter();

private:
	Voice* getFreeVoice();

private:
    std::vector<Voice*> _voices;

    std::size_t _size;
};



#endif  // VOICESVECTOR_H
