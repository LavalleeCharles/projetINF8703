/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Synthesizer.h"
#include "OscillatorGUI.h"
#include "FilterGUI.h"
#include "EnvelopeGUI.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible(_synth);

        addAndMakeVisible(_oscillatorGUI);

        addAndMakeVisible(_filterGUI);

        addAndMakeVisible(_envelopeGUI);
        _envelopeGUI.setSynth(&_synth);

        setSize (1000, 600);
    }

    ~MainContentComponent()
    {
    }

    //=======================================================================
    void paint (Graphics& /*g*/) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        // g.fillAll (Colours::black);
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        _oscillatorGUI.setTopLeftPosition(0, 0);
        _oscillatorGUI.resized();

        _filterGUI.setTopLeftPosition(0, 80);
        _filterGUI.resized();

        _envelopeGUI.setTopLeftPosition(0, 160);
        _envelopeGUI.resized();

        _synth.setTopLeftPosition(0, 260);
        _synth.resized();
    }


private:
    //==============================================================================

    // Your private member variables go here...
    Synthesizer _synth;

    OscillatorGUI _oscillatorGUI;
    FilterGUI _filterGUI;
    EnvelopeGUI _envelopeGUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
