#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "VoicesVector.h"
#include "Midi.h"

// TODO : redesign de la structure du code??
class Synthesizer   : public AudioAppComponent
{
public:
    //==============================================================================
    Synthesizer()
    {
        addAndMakeVisible(midi);
        midi.setVoicesVector(&_voices);

        _voices.setNumberOfVoices(64);

        setSize (1000, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    ~Synthesizer()
    {
        shutdownAudio();
    }

    //=======================================================================

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()

        Voice::setSampleRate(sampleRate);

        String message;
        message << "samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
        message << "sampleRate = " << sampleRate << newLine;
        Logger::getCurrentLogger()->writeToLog(message);
    }


    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!
        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        /*
        float *const buffer0 = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        float *const buffer1 = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
        for (int i = 0; i < bufferToFill.numSamples; ++i) {
            float value = _phase <= M_PI ? 1.0: -1.0;
            buffer0[i] = value * 0.5f;
            buffer1[i] = value * 0.5f;

            _phase += _phaseStep;
            if (_phase >= M_2_PI) {

            }
        }*/

        float *const buffer0 = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        float *const buffer1 = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
        for (int i = 0; i < bufferToFill.numSamples; ++i) {
            float value = _voices.nextSample();
            buffer0[i] = value * 0.25;
            buffer1[i] = value * 0.25;
        }
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()

        Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
    }

    //=======================================================================
    void paint (Graphics& /*g*/) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        // g.fillAll (Colours::black);

        /*
        if (this->isShowing()) {
            midi.setFocus();
        }
         */
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any ch
        // ild components, this is where you should
        // update their positions.

        midi.resized();
    }

    void focusGained(FocusChangeType /*cause*/) override
    {
        //midi.setFocus();
    }

    void moved() override
    {
        //midi.setFocus();
    }

    void broughtToFront() override
    {
        //midi.setFocus();
    }


    void updateEnvelope(double value, Envelope::envelopeParamIndex paramId) {
        _voices.updateEnvelope(value, paramId);
    }


    void setDefaultEnvelopeValues(double dEnvAtkLvl, double dEnvDcyLvl, double dEnvAtkRt, double dEnvDcyRt, double dEnvRelRt) {
        Voice::setWaveType(Oscillateur::sine);
        _voices.updateEnvelope(dEnvAtkLvl, Envelope::attackLevel);
        _voices.updateEnvelope(dEnvDcyLvl, Envelope::decayLevel);
        _voices.updateEnvelope(dEnvAtkRt, Envelope::attackRate);
        _voices.updateEnvelope(dEnvDcyRt, Envelope::decayRate);
        _voices.updateEnvelope(dEnvRelRt, Envelope::releaseRate);
    }

    void setDefaultFilterValues(int dFilType, double dFilCut, double dFilRes) {
        Voice::setFilterType(dFilType);
        Voice::setFilterCutoff(dFilCut);
        Voice::setFilterResonance(dFilRes);
    }

private:
    //==============================================================================
    VoicesVector _voices;

    Midi midi; // TODO : midi dans le MainComponent?
};


#endif  // SYNTHESIZER_H
