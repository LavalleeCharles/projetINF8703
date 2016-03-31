#ifndef OSCILLATORGUI_H
#define OSCILLATORGUI_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Voice.h"


class OscillatorGUI : public Component,
                      private ComboBox::Listener
{
public:
    OscillatorGUI()
    {
        addAndMakeVisible(_oscillatorLabel);
        _oscillatorLabel.setText("OSCILLATOR", dontSendNotification);

        // Oscillateur wave type
        addAndMakeVisible(_filterWaveTypeComboBox);
        StringArray waveTypesLabel = { "Sine", "Saw", "Square", "Triangle" };
        _filterWaveTypeComboBox.addItemList(waveTypesLabel, 1);
        _filterWaveTypeComboBox.setSelectedId(1, dontSendNotification);
        _filterWaveTypeComboBox.addListener(this);

        addAndMakeVisible(_filterWaveTypeLabel);
        _filterWaveTypeLabel.setText("Wave Type", dontSendNotification);
        _filterWaveTypeLabel.attachToComponent(&_filterWaveTypeComboBox, true);

        setSize(800, 80);
    }

    ~OscillatorGUI()
    {

    }

    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        // g.fillAll (Colours::black);
        g.drawRoundedRectangle(10, 10, 610, 70, 10, 1);
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        _oscillatorLabel.setBounds(10, 20, 80, 20);
        _filterWaveTypeComboBox.setBounds(120, 40, 80, 20);
    }


private:
    void comboBoxChanged(ComboBox* comboBox) override
    {
        if (comboBox == &_filterWaveTypeComboBox) {
            Voice::setWaveType(comboBox->getSelectedItemIndex());
            //midi.setFocus();
        }
    }

private:
    Label _oscillatorLabel;

    ComboBox _filterWaveTypeComboBox;
    Label _filterWaveTypeLabel;
};



#endif  // OSCILLATORGUI_H
