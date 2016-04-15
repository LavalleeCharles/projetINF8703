#ifndef FILTERGUI_H
#define FILTERGUI_H


#include "../JuceLibraryCode/JuceHeader.h"
#include "Synthesizer.h"


class FilterGUI : public Component,
                  private ComboBox::Listener,
                  private Slider::Listener
{
public:
    FilterGUI()
    {
        addAndMakeVisible(_filterLabel);
        _filterLabel.setText("FILTER", dontSendNotification);

        // Filter Type
        addAndMakeVisible(_filterTypeComboBox);
        StringArray filterTypesLabel = { "Low Pass", "High Pass", "Band Pass", "No Filter" };
        _filterTypeComboBox.addItemList(filterTypesLabel , 1);
        _filterTypeComboBox.addListener(this);
        addAndMakeVisible(_filterTypeLabel);
        _filterTypeLabel.setText("Filter Type", dontSendNotification);
        _filterTypeLabel.attachToComponent(&_filterTypeComboBox, true);

        // Filter Cutoff
        addAndMakeVisible(_filterCutoffValue);
        _filterCutoffValue.setRange(1, 22000);
        _filterCutoffValue.setSkewFactor(0.5);
        _filterCutoffValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _filterCutoffValue.getTextBoxHeight());
        _filterCutoffValue.setTextValueSuffix(" Hz");
        _filterCutoffValue.addListener(this);
        addAndMakeVisible(_filterCutoffLabel);
        _filterCutoffLabel.setText("Cutoff:", dontSendNotification);
        _filterCutoffLabel.attachToComponent(&_filterCutoffValue, true);

        // Filter Resonance
        addAndMakeVisible(_filterResValue);
        _filterResValue.setRange(0.01, 0.99);
        _filterResValue.setTextValueSuffix(" ");
        _filterResValue.setTextBoxStyle(Slider::TextBoxLeft, false, 80, _filterResValue.getTextBoxHeight());
        _filterResValue.addListener(this);
        addAndMakeVisible(_filterResLabel);
        _filterResLabel.setText("Resonance:", dontSendNotification);
        _filterResLabel.attachToComponent(&_filterResValue, true);

        _width = 1000;
        _height = 80;

        setSize(_width, _height);
    }

    ~FilterGUI()
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
        _filterLabel.setBounds(10, height_4, 80, height_4);
        _filterTypeComboBox.setBounds(120, height_4 + 20, 80, height_4);
        _filterCutoffValue.setBounds(320, height_4 + 20, 180, height_4);
        _filterResValue.setBounds(620, height_4 + 20, 180, height_4);
    }

    void setDefaultValue(int dFilType, double dFilCut, double dFilRes) {
        _filterTypeComboBox.setSelectedId(dFilType + 1, dontSendNotification);
        _filterCutoffValue.setValue(dFilCut);
        _filterResValue.setValue(dFilRes);

    }


private:
    void comboBoxChanged(ComboBox* comboBox) override
    {
        if (comboBox == &_filterTypeComboBox) {
            _synth->updateFilterType(comboBox->getSelectedItemIndex());
            //std::cout << comboBox->getSelectedItemIndex() << std::endl;
            //midi.setFocus();
        }
    }

    void sliderValueChanged(Slider* slider) override
    {
        if (slider == &_filterCutoffValue) {
            _synth->updateFilterCutoff(slider->getValue());
            //midi.setFocus();
        } else if (slider == &_filterResValue) {
            _synth->updateFilterRes(slider->getValue());
            //midi.setFocus();
        }
    }


private:
    Synthesizer* _synth;

    int _width;
    int _height;

    Label _filterLabel;

    ComboBox _filterTypeComboBox;
    Label _filterTypeLabel;

    Slider _filterCutoffValue;
    Label _filterCutoffLabel;

    Slider _filterResValue;
    Label _filterResLabel;

};



#endif  // FILTERGUI_H
