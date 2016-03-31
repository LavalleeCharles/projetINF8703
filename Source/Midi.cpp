#include "Midi.h"

Midi::Midi() : lastInputIndex(0),
               isAddingFromMidiInput(false),
               keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard),
               startTime(Time::getMillisecondCounterHiRes() * 0.001)
{
    addAndMakeVisible(midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    const StringArray midiInputs(MidiInput::getDevices());
    midiInputList.addItemList(midiInputs, 1);
    midiInputList.addListener(this);
    addAndMakeVisible(midiInputListLabel);
    midiInputListLabel.setText("Midi Device", dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);

    // Find the first enabled device
    for (int i = 0; i < midiInputs.size(); ++i) {
        if (deviceManager.isMidiInputEnabled(midiInputs[i])) {

            setMidiInput(i);
            break;
        }
    }
    // If no device is found
    if (midiInputList.getSelectedId() == 0) {
        setMidiInput(0);
    }

    addAndMakeVisible(keyboardComponent);
    keyboardState.addListener(this);

    addAndMakeVisible (midiMessagesBox);
    midiMessagesBox.setMultiLine (true);
    midiMessagesBox.setReturnKeyStartsNewLine (true);
    midiMessagesBox.setReadOnly (true);
    midiMessagesBox.setScrollbarsShown (true);
    midiMessagesBox.setCaretVisible (false);
    midiMessagesBox.setPopupMenuEnabled (true);
    midiMessagesBox.setColour (TextEditor::backgroundColourId, Colour (0x32ffffff));
    midiMessagesBox.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    midiMessagesBox.setColour (TextEditor::shadowColourId, Colour (0x16000000));

    _voices = nullptr;

    setSize (getParentWidth(), 600);
}


Midi::~Midi()
{
    keyboardState.removeListener(this);
    deviceManager.removeMidiInputCallback (MidiInput::getDevices()[midiInputList.getSelectedItemIndex()], this);
    midiInputList.removeListener(this);
}


void Midi::resized() {
    //Rectangle<int> area(getLocalBounds());
    midiInputList.setBounds(120, 20, 200, 20);
    keyboardComponent.setBounds(10, 60, (getWidth() - 990), 60);
    midiMessagesBox.setBounds(10, 120, (getWidth() - 990), 300);
}


int Midi::getNumberOfKeyboardNotes() const
{
    return keyboardComponent.getRangeEnd() - keyboardComponent.getRangeStart();
}


void Midi::setFocus()
{
    keyboardComponent.grabKeyboardFocus();
    keyboardComponent.toFront(true);
}


void Midi::setMidiInput(int id)
{
    const StringArray list (MidiInput::getDevices());

    deviceManager.removeMidiInputCallback (list[lastInputIndex], this);

    const String newInput (list[id]);

    if (! deviceManager.isMidiInputEnabled (newInput))
        deviceManager.setMidiInputEnabled (newInput, true);

    deviceManager.addMidiInputCallback (newInput, this);
    midiInputList.setSelectedId (id + 1, dontSendNotification);

    lastInputIndex = id;
}


void Midi::handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message)
{
    const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
    keyboardState.processNextMidiEvent (message);
    postMessageToList (message, source->getName());
}


void Midi::handleNoteOn(MidiKeyboardState* , int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isAddingFromMidiInput) {
        MidiMessage m (MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
        //_midiNotesOn[midiNoteNumber] = true;
        _voices->noteOn(midiNoteNumber, velocity);

        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keybaord");
    }
}


void Midi::handleNoteOff(MidiKeyboardState* , int midiChannel, int midiNoteNumber, float velocity)
{
    if (!isAddingFromMidiInput) {
        MidiMessage m (MidiMessage::noteOff (midiChannel, midiNoteNumber));
        //_midiNotesOn[midiNoteNumber] = false;
        _voices->noteOff(midiNoteNumber, velocity);

        m.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001);
        postMessageToList (m, "On-Screen Keyboard");
    }
}


void Midi::comboBoxChanged(ComboBox* comboBox) {
    if (comboBox == &midiInputList) {
        setMidiInput(midiInputList.getSelectedItemIndex());
        setFocus();
    }
}
