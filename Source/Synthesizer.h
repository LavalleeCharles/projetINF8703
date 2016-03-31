#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "VoicesVector.h"
#include "Midi.h"

#include "FilterGUI.h"


// TODO : redesign de la structure du code


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class Synthesizer   : public AudioAppComponent,
                      private ComboBox::Listener
{
public:
    //==============================================================================
    Synthesizer()
    {
        addAndMakeVisible(waveTypeComboBox);
        StringArray waveTypesLabel = { "Sine", "Saw", "Square", "Triangle" };
        waveTypeComboBox.addItemList(waveTypesLabel, 1);
        waveTypeComboBox.setSelectedId(1, dontSendNotification);
        waveTypeComboBox.addListener(this);

        addAndMakeVisible(waveTypeLabel);
        waveTypeLabel.setText("Wave Type", dontSendNotification);
        waveTypeLabel.attachToComponent(&waveTypeComboBox, true);

        addAndMakeVisible(_filterGUI);

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
        for (size_t i = 0; i < _voices.size(); ++i) {
            _voices[i]->setAttackRate((unsigned long long)(sampleRate * 0.1));
            _voices[i]->setDecayRate((unsigned long long)(sampleRate * 0.5));
            _voices[i]->setReleaseRate((unsigned long long)(sampleRate * 0.5));
        }
		
        String message;
        message << "samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
        message << "sampleRate = " << sampleRate << newLine;
        Logger::getCurrentLogger()->writeToLog(message);
    }


    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!
        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        //for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
            float *const buffer0 = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
			float *const buffer1 = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
            for (int i = 0; i < bufferToFill.numSamples; ++i) {
				float value = _voices.nextSample();
				buffer0[i] = value; 
				buffer1[i] = value;
            }

        //}
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
        waveTypeComboBox.setBounds(120, 20, 80, 20);

        _filterGUI.setTopLeftPosition(0, 40);
        _filterGUI.resized();

        midi.setTopLeftPosition(0, 80);
        midi.resized();
    }

    void focusGained(FocusChangeType /*cause*/) override
    {
        midi.setFocus();
    }

    void moved() override
    {
        midi.setFocus();
    }

    void broughtToFront() override
    {
        midi.setFocus();
    }


private:
    void comboBoxChanged(ComboBox* comboBox) override
    {
        if (comboBox == &waveTypeComboBox) {
			Voice::setWaveType(comboBox->getSelectedItemIndex());
            midi.setFocus();
        }
    }


private:
    //==============================================================================
    VoicesVector _voices;

    ComboBox waveTypeComboBox;
    Label waveTypeLabel;

    Midi midi; // TODO : midi dans le MainComponent?

    FilterGUI _filterGUI;
};


#endif  // SYNTHESIZER_H
