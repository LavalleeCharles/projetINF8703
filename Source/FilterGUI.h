#ifndef FILTERGUI_H
#define FILTERGUI_H


#include "../JuceLibraryCode/JuceHeader.h"
#include "Voice.h"


class FilterGUI : public Component,
                  private ComboBox::Listener,
                  private Label::Listener
{
public:
    FilterGUI()
    {
        // Filter Type
        addAndMakeVisible(_filterTypeComboBox);
        StringArray filterTypesLabel = { "Low Pass", "High Pass", "Band Pass" };
        _filterTypeComboBox.addItemList(filterTypesLabel , 1);
        _filterTypeComboBox.setSelectedId(1, dontSendNotification);
        _filterTypeComboBox.addListener(this);
        addAndMakeVisible(_filterTypeLabel);
        _filterTypeLabel.setText("Filter Type", dontSendNotification);
        _filterTypeLabel.attachToComponent(&_filterTypeComboBox, true);

        // Filter Cutoff
        addAndMakeVisible(_filterCutoffValue);
        _filterCutoffValue.setText("1000.0", dontSendNotification);
        _filterCutoffValue.setEditable(true);
        _filterCutoffValue.setColour(Label::backgroundColourId, Colours::white);
        _filterCutoffValue.setColour(Label::outlineColourId, Colours::grey);
        _filterCutoffValue.addListener(this);
        addAndMakeVisible(_filterCutoffLabel);
        _filterCutoffLabel.setText("Cutoff:", dontSendNotification);
        _filterCutoffLabel.attachToComponent(&_filterCutoffValue, true);

        // Filter Resonance
        addAndMakeVisible(_filterResValue);
        _filterResValue.setText("0.1", dontSendNotification);
        _filterResValue.setEditable(true);
        _filterResValue.setColour(Label::backgroundColourId, Colours::white);
        _filterResValue.setColour(Label::outlineColourId, Colours::grey);
        _filterResValue.addListener(this);
        addAndMakeVisible(_filterResLabel);
        _filterResLabel.setText("Resonance:", dontSendNotification);
        _filterResLabel.attachToComponent(&_filterResValue, true);

        setSize(600, 60);
    }

    ~FilterGUI()
    {

    }

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
        _filterTypeComboBox.setBounds(120, 20, 80, 20);
        _filterCutoffValue.setBounds(320, 20, 80, 20);
        _filterResValue.setBounds(520, 20, 80, 20);
    }


private:
    void comboBoxChanged(ComboBox* comboBox) override
    {
        if (comboBox == &_filterTypeComboBox) {
            Voice::setFilterType(comboBox->getSelectedItemIndex());
            //midi.setFocus();
        }
    }

    void labelTextChanged(Label* label) override
    {
        if (label == &_filterCutoffValue) {
            double f = label->getText().getDoubleValue();
            Voice::setFilterCutoff(f);
            //midi.setFocus();
        } else if (label == &_filterResValue) {
            double r = label->getText().getDoubleValue();
            Voice::setFilterResonance(r);
            //midi.setFocus();
        }
    }


private:
    ComboBox _filterTypeComboBox;
    Label _filterTypeLabel;

    Label _filterCutoffValue;
    Label _filterCutoffLabel;

    Label _filterResValue;
    Label _filterResLabel;

};



#endif  // FILTERGUI_H
