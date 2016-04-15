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
#include "LfoGUI.h"

/*
TODO: -- list --
 - Clean code (rename stuff)
 - LFO
 - normalize output? (polyphonic is too loud)
 - PolyBlep ?
 - remove hardCoded value in GUI
 - add effects ?
 - multi oscillator
 - filter envelope
 - vibrato
 - mem leak...
*/



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
        // Default envelope values
        double _defaultEnvelopeAttackLevel = 1.0;
        double _defaultEnvelopeDecayLevel = 0.8;
        double _defaultEnvelopeAttackRate = 0.1;
        double _defaultEnvelopeDecayRate = 0.3;
        double _defaultEnvelopeReleaseRate = 0.3;

        // Default filter values
        int _defaultFilterType = noFilter;
        double _defaultFilterCutoff = 1000.0;
        double _defaultFilterResonance = 0.1;


        addAndMakeVisible(_synth);
        _synth.setDefaultEnvelopeValues(_defaultEnvelopeAttackLevel,
                                        _defaultEnvelopeDecayLevel,
                                        _defaultEnvelopeAttackRate,
                                        _defaultEnvelopeDecayRate,
                                        _defaultEnvelopeReleaseRate);

        addAndMakeVisible(_oscillatorGUI); // TODO ?
        _oscillatorGUI.setSynth(&_synth);

        addAndMakeVisible(_filterGUI);
        _filterGUI.setDefaultValue(_defaultFilterType,
                                   _defaultFilterCutoff,
                                   _defaultFilterResonance);
        _filterGUI.setSynth(&_synth);

        addAndMakeVisible(_envelopeGUI);
        _envelopeGUI.setDefaultValue(_defaultEnvelopeAttackLevel,
                                     _defaultEnvelopeDecayLevel,
                                     _defaultEnvelopeAttackRate,
                                     _defaultEnvelopeDecayRate,
                                     _defaultEnvelopeReleaseRate);
        _envelopeGUI.setSynth(&_synth);

        addAndMakeVisible(_lfoGUI);
        _lfoGUI.setSynth(&_synth);

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

        _lfoGUI.setTopLeftPosition(0, 160);
        _lfoGUI.resized();

        _envelopeGUI.setTopLeftPosition(0, 240);
        _envelopeGUI.resized();

        _synth.setTopLeftPosition(0, 340);
        _synth.resized();
    }


private:
    //==============================================================================

    // Your private member variables go here...
    Synthesizer _synth;

    OscillatorGUI _oscillatorGUI;
    FilterGUI _filterGUI;
    EnvelopeGUI _envelopeGUI;
    LfoGUI _lfoGUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
