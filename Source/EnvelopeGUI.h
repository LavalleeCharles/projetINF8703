#ifndef ENVELOPEGUI_H
#define ENVELOPEGUI_H


#include "../JuceLibraryCode/JuceHeader.h"
#include "Synthesizer.h"


class EnvelopeGUI : public Component,
                     private Label::Listener
{
public:
    EnvelopeGUI()
    {
        addAndMakeVisible(_envelopeLabel);
        _envelopeLabel.setText("ENVELOPE", dontSendNotification);

        // Envelope Attack Level
        addAndMakeVisible(_envelopeAttackLevelValue);
        _envelopeAttackLevelValue.setText("1.0", dontSendNotification);
        _envelopeAttackLevelValue.setEditable(true);
        _envelopeAttackLevelValue.setColour(Label::backgroundColourId, Colours::white);
        _envelopeAttackLevelValue.setColour(Label::outlineColourId, Colours::grey);
        _envelopeAttackLevelValue.addListener(this);
        addAndMakeVisible(_envelopeAttackLevelLabel);
        _envelopeAttackLevelLabel.setText("Attack Level:", dontSendNotification);
        _envelopeAttackLevelLabel.attachToComponent(&_envelopeAttackLevelValue, true);

        // Envelope Decay Level
        addAndMakeVisible(_envelopeDecayLevelValue);
        _envelopeDecayLevelValue.setText("0.8", dontSendNotification);
        _envelopeDecayLevelValue.setEditable(true);
        _envelopeDecayLevelValue.setColour(Label::backgroundColourId, Colours::white);
        _envelopeDecayLevelValue.setColour(Label::outlineColourId, Colours::grey);
        _envelopeDecayLevelValue.addListener(this);
        addAndMakeVisible(_envelopeDecayLevelLabel);
        _envelopeDecayLevelLabel.setText("Decay Level:", dontSendNotification);
        _envelopeDecayLevelLabel.attachToComponent(&_envelopeDecayLevelValue, true);

        // Envelope Attack Rate
        addAndMakeVisible(_envelopeAttackRateValue);
        _envelopeAttackRateValue.setText("1.0", dontSendNotification);
        _envelopeAttackRateValue.setEditable(true);
        _envelopeAttackRateValue.setColour(Label::backgroundColourId, Colours::white);
        _envelopeAttackRateValue.setColour(Label::outlineColourId, Colours::grey);
        _envelopeAttackRateValue.addListener(this);
        addAndMakeVisible(_envelopeAttackRateLabel);
        _envelopeAttackRateLabel.setText("Attack Rate:", dontSendNotification);
        _envelopeAttackRateLabel.attachToComponent(&_envelopeAttackRateValue, true);

        // Envelope Decay Rate
        addAndMakeVisible(_envelopeDecayRateValue);
        _envelopeDecayRateValue.setText("1.0", dontSendNotification);
        _envelopeDecayRateValue.setEditable(true);
        _envelopeDecayRateValue.setColour(Label::backgroundColourId, Colours::white);
        _envelopeDecayRateValue.setColour(Label::outlineColourId, Colours::grey);
        _envelopeDecayRateValue.addListener(this);
        addAndMakeVisible(_envelopeDecayRateLabel);
        _envelopeDecayRateLabel.setText("Decay Rate:", dontSendNotification);
        _envelopeDecayRateLabel.attachToComponent(&_envelopeDecayRateValue, true);

        // Envelope Release Rate
        addAndMakeVisible(_envelopeReleaseRateValue);
        _envelopeReleaseRateValue.setText("1.0", dontSendNotification);
        _envelopeReleaseRateValue.setEditable(true);
        _envelopeReleaseRateValue.setColour(Label::backgroundColourId, Colours::white);
        _envelopeReleaseRateValue.setColour(Label::outlineColourId, Colours::grey);
        _envelopeReleaseRateValue.addListener(this);
        addAndMakeVisible(_envelopeReleaseRateLabel);
        _envelopeReleaseRateLabel.setText("Release Rate:", dontSendNotification);
        _envelopeReleaseRateLabel.attachToComponent(&_envelopeReleaseRateValue, true);


        setSize(800, 100);
    }

    ~EnvelopeGUI()
    {

    }


    void setSynth(Synthesizer *synth) {
        _synth = synth;
    }


    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        // g.fillAll (Colours::black);
        g.drawRoundedRectangle(10, 10, 610, 90, 10, 1);
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        _envelopeLabel.setBounds(10, 20, 80, 20);
        _envelopeAttackLevelValue.setBounds(120, 40, 80, 20);
        _envelopeDecayLevelValue.setBounds(320, 40, 80, 20);
        _envelopeAttackRateValue.setBounds(120, 60, 80, 20);
        _envelopeDecayRateValue.setBounds(320, 60, 80, 20);
        _envelopeReleaseRateValue.setBounds(520, 60, 80, 20);
    }


private:
    void labelTextChanged(Label* label) override
    {
        if (label == &_envelopeAttackLevelValue) {
            _synth->updateEnvelope(label->getText().getDoubleValue(), Envelope::attackLevel);
            //midi.setFocus();
        } else if (label == &_envelopeDecayLevelValue) {
            _synth->updateEnvelope(label->getText().getDoubleValue(), Envelope::decayLevel);
            //midi.setFocus();
        } else if (label == &_envelopeAttackRateValue) {
            _synth->updateEnvelope(label->getText().getDoubleValue(), Envelope::attackRate);
            //midi.setFocus();
        } else if (label == &_envelopeDecayRateValue) {
            _synth->updateEnvelope(label->getText().getDoubleValue(), Envelope::decayRate);
            //midi.setFocus();
        } else if (label == &_envelopeReleaseRateValue) {
            _synth->updateEnvelope(label->getText().getDoubleValue(), Envelope::releaseRate);
            //midi.setFocus();
        }
    }


private:
    Synthesizer* _synth;
    Label _envelopeLabel;

    Label _envelopeAttackLevelValue;
    Label _envelopeAttackLevelLabel;

    Label _envelopeDecayLevelValue;
    Label _envelopeDecayLevelLabel;

    Label _envelopeAttackRateValue;
    Label _envelopeAttackRateLabel;

    Label _envelopeDecayRateValue;
    Label _envelopeDecayRateLabel;

    Label _envelopeReleaseRateValue;
    Label _envelopeReleaseRateLabel;
};


#endif  // ENVELOPEGUI_H
