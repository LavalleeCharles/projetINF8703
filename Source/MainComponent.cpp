/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillateur.h"
#include "Midi.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent,
                               private ComboBox::Listener
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible(waveTypeComboBox);
        StringArray waveTypesLabel = {"Sine", "Saw", "Square", "Triangle"};
        waveTypeComboBox.addItemList(waveTypesLabel, 1);
        waveTypeComboBox.setSelectedId(1, dontSendNotification);
        waveTypeComboBox.addListener(this);

        addAndMakeVisible(waveTypeLabel);
        waveTypeLabel.setText("Wave Type", dontSendNotification);
        waveTypeLabel.attachToComponent(&waveTypeComboBox, true);

        addAndMakeVisible(midi);

        setSize (1000, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
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
        oscillateur.setSampleRate((float)sampleRate);

        String message;
        message << "samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
        message << "sampleRate = " << sampleRate << newLine;
        Logger::getCurrentLogger()->writeToLog(message);
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!
        // For more details, see the help for AudioProcessor::getNextAudioBlock()
        if (midi.isNotePlaying()) {
            oscillateur.setFrequency(midi.getMidiNote());

            for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
                float *const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
                oscillateur.play(buffer, bufferToFill.numSamples);
            }
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
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        // g.fillAll (Colours::black);

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        const int comboBoxLeft = 120;
        waveTypeComboBox.setBounds(comboBoxLeft, 20, 80, 20);
        midi.setTopLeftPosition(0, 40);
        midi.resized();
    }

    void focusGained(FocusChangeType cause) override
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
            oscillateur.setWaveType(comboBox->getSelectedItemIndex());
            midi.setFocus();
        }
    }


private:
    //==============================================================================

    // Your private member variables go here...
    Oscillateur oscillateur;

    ComboBox waveTypeComboBox;
    Label waveTypeLabel;

    Midi midi;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
