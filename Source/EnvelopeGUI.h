#ifndef ENVELOPEGUI_H
#define ENVELOPEGUI_H


#include "../JuceLibraryCode/JuceHeader.h"
#include "Synthesizer.h"


class EnvelopeGUI : public Component,
                     private Slider::Listener
{
public:
    EnvelopeGUI()
    {
        addAndMakeVisible(_envelopeLabel);
        _envelopeLabel.setText("ENVELOPE", dontSendNotification);

        // Envelope Attack Level
        addAndMakeVisible(_envelopeAttackLevelValue);
        _envelopeAttackLevelValue.setRange(0.01, 1.0);
        _envelopeAttackLevelValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _envelopeAttackLevelValue.getTextBoxHeight());
        _envelopeAttackLevelValue.addListener(this);
        addAndMakeVisible(_envelopeAttackLevelLabel);
        _envelopeAttackLevelLabel.setText("Attack Level:", dontSendNotification);
        _envelopeAttackLevelLabel.attachToComponent(&_envelopeAttackLevelValue, true);

        // Envelope Decay Level
        addAndMakeVisible(_envelopeDecayLevelValue);
        _envelopeDecayLevelValue.setRange(0.01, 1.0);
        _envelopeDecayLevelValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _envelopeAttackLevelValue.getTextBoxHeight());
        _envelopeDecayLevelValue.addListener(this);
        addAndMakeVisible(_envelopeDecayLevelLabel);
        _envelopeDecayLevelLabel.setText("Decay Level:", dontSendNotification);
        _envelopeDecayLevelLabel.attachToComponent(&_envelopeDecayLevelValue, true);

        // Envelope Attack Rate
        addAndMakeVisible(_envelopeAttackRateValue);
        _envelopeAttackRateValue.setRange(0.01, 2.0);
        _envelopeAttackRateValue.setSkewFactor(0.5);
        _envelopeAttackRateValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _envelopeAttackLevelValue.getTextBoxHeight());
        _envelopeAttackRateValue.setTextValueSuffix(" s");
        _envelopeAttackRateValue.addListener(this);
        addAndMakeVisible(_envelopeAttackRateLabel);
        _envelopeAttackRateLabel.setText("Attack Rate:", dontSendNotification);
        _envelopeAttackRateLabel.attachToComponent(&_envelopeAttackRateValue, true);

        // Envelope Decay Rate
        addAndMakeVisible(_envelopeDecayRateValue);
        _envelopeDecayRateValue.setRange(0.01, 2.0);
        _envelopeDecayRateValue.setSkewFactor(0.5);
        _envelopeDecayRateValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _envelopeAttackLevelValue.getTextBoxHeight());
        _envelopeDecayRateValue.setTextValueSuffix(" s");
        _envelopeDecayRateValue.addListener(this);
        addAndMakeVisible(_envelopeDecayRateLabel);
        _envelopeDecayRateLabel.setText("Decay Rate:", dontSendNotification);
        _envelopeDecayRateLabel.attachToComponent(&_envelopeDecayRateValue, true);

        // Envelope Release Rate
        addAndMakeVisible(_envelopeReleaseRateValue);
        _envelopeReleaseRateValue.setRange(0.0, 5.0);
        _envelopeReleaseRateValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _envelopeAttackLevelValue.getTextBoxHeight());
        _envelopeReleaseRateValue.setSkewFactor(0.8);
        _envelopeReleaseRateValue.setTextValueSuffix(" s");
        _envelopeReleaseRateValue.addListener(this);
        addAndMakeVisible(_envelopeReleaseRateLabel);
        _envelopeReleaseRateLabel.setText("Release Rate:", dontSendNotification);
        _envelopeReleaseRateLabel.attachToComponent(&_envelopeReleaseRateValue, true);

        _width = 1100;
        _height = 100;

        setSize(_width, _height);
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
        g.drawRoundedRectangle(10, 10, _width - 190, _height - 10, 10, 1);
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        int height_4 = _height / 4;
        _envelopeLabel.setBounds(10, height_4, 80, height_4);
        _envelopeAttackLevelValue.setBounds(120, height_4 + 20, 180, height_4);
        _envelopeDecayLevelValue.setBounds(420, height_4 + 20, 180, height_4);
        _envelopeAttackRateValue.setBounds(120, height_4 + 40, 180, height_4);
        _envelopeDecayRateValue.setBounds(420, height_4 + 40, 180, height_4);
        _envelopeReleaseRateValue.setBounds(720, height_4 + 40, 180, height_4);
    }

    void setDefaultValue(double dEnvAtkLvl, double dEnvDcyLvl, double dEnvAtkRt, double dEnvDcyRt, double dEnvRelRt) {
        _envelopeAttackLevelValue.setValue(dEnvAtkLvl);
        _envelopeDecayLevelValue.setValue(dEnvDcyLvl);
        _envelopeAttackRateValue.setValue(dEnvAtkRt);
        _envelopeDecayRateValue.setValue(dEnvDcyRt);
        _envelopeReleaseRateValue.setValue(dEnvRelRt);
    }


private:
    void sliderValueChanged(Slider* slider) override
    {
        if (slider == &_envelopeAttackLevelValue) {
            _synth->updateEnvelope(slider->getValue(), Envelope::attackLevel);
            //midi.setFocus();
        } else if (slider == &_envelopeDecayLevelValue) {
            _synth->updateEnvelope(slider->getValue(), Envelope::decayLevel);
            //midi.setFocus();
        } else if (slider == &_envelopeAttackRateValue) {
            _synth->updateEnvelope(slider->getValue(), Envelope::attackRate);
            //midi.setFocus();
        } else if (slider == &_envelopeDecayRateValue) {
            _synth->updateEnvelope(slider->getValue(), Envelope::decayRate);
            //midi.setFocus();
        } else if (slider == &_envelopeReleaseRateValue) {
            _synth->updateEnvelope(slider->getValue(), Envelope::releaseRate);
            //midi.setFocus();
        }
    }


private:
    int _width;
    int _height;

    Synthesizer* _synth;
    Label _envelopeLabel;

    Slider _envelopeAttackLevelValue;
    Label _envelopeAttackLevelLabel;

    Slider _envelopeDecayLevelValue;
    Label _envelopeDecayLevelLabel;

    Slider _envelopeAttackRateValue;
    Label _envelopeAttackRateLabel;

    Slider _envelopeDecayRateValue;
    Label _envelopeDecayRateLabel;

    Slider _envelopeReleaseRateValue;
    Label _envelopeReleaseRateLabel;
};


#endif  // ENVELOPEGUI_H
