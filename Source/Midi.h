#ifndef MIDI_H
#define MIDI_H

#include "../JuceLibraryCode/JuceHeader.h"

// Basé sur: https://www.juce.com/doc/tutorial_handling_midi_events
class Midi : public Component,
             private MidiInputCallback,
             private MidiKeyboardStateListener,
             private ComboBox::Listener
{
public:
    Midi();
    ~Midi();

    void resized() override;
    int getMidiNote() const;
    bool isNotePlaying() const;
    void resetKeyboardState();

    void setFocus();

private:
    void setMidiInput(int id);
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void handleNoteOn(MidiKeyboardState* , int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState* , int midiChannel, int midiNoteNumber, float velocity) override;
    void comboBoxChanged(ComboBox* comboBox) override;


    static String getMidiMessageDescription (const MidiMessage& m)
    {
        if (m.isNoteOn())           return "Note on "  + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3);
        if (m.isProgramChange())    return "Program change " + String (m.getProgramChangeNumber());
        if (m.isPitchWheel())       return "Pitch wheel " + String (m.getPitchWheelValue());
        if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName (m.getNoteNumber(), true, true, 3) +  ": " + String (m.getAfterTouchValue());
        if (m.isChannelPressure())  return "Channel pressure " + String (m.getChannelPressureValue());
        if (m.isAllNotesOff())      return "All notes off";
        if (m.isAllSoundOff())      return "All sound off";
        if (m.isMetaEvent())        return "Meta event";

        if (m.isController())
        {
            String name (MidiMessage::getControllerName (m.getControllerNumber()));

            if (name.isEmpty())
                name = "[" + String (m.getControllerNumber()) + "]";

            return "Controller " + name + ": " + String (m.getControllerValue());
        }

        return String::toHexString (m.getRawData(), m.getRawDataSize());
    }

    void logMessage (const String& m)
    {
        midiMessagesBox.moveCaretToEnd();
        midiMessagesBox.insertTextAtCaret (m + newLine);
    }

// This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public CallbackMessage
    {
    public:
        IncomingMessageCallback (Midi* o, const MidiMessage& m, const String& s)
                : owner(o), message (m), source (s)
        {}

        void messageCallback() override
        {
            if (owner != nullptr)
                owner->addMessageToList (message, source);
        }

        Component::SafePointer<Midi> owner;
        MidiMessage message;
        String source;
    };

    void postMessageToList (const MidiMessage& message, const String& source)
    {
        (new IncomingMessageCallback (this, message, source))->post();
    }

    void addMessageToList (const MidiMessage& message, const String& source)
    {
        const double time = message.getTimeStamp() - startTime;

        const int hours = ((int) (time / 3600.0)) % 24;
        const int minutes = ((int) (time / 60.0)) % 60;
        const int seconds = ((int) time) % 60;
        const int millis = ((int) (time * 1000.0)) % 1000;

        const String timecode (String::formatted ("%02d:%02d:%02d.%03d",
                                                  hours,
                                                  minutes,
                                                  seconds,
                                                  millis));

        const String description (getMidiMessageDescription (message));
        const String noteNumber (message.getNoteNumber());
        float test = 440.f * std::pow(2.f, (message.getNoteNumber() - 69) / 12.f);
        const String frequency (test);

        const String midiMessageString (timecode + "  -  " + description + " (" + source + ")" + " Note: " + noteNumber + " f: " + frequency + " Hz"); // [7]
        logMessage (midiMessageString);
    }

private:
    AudioDeviceManager deviceManager;
    ComboBox midiInputList;
    Label midiInputListLabel;
    int lastInputIndex;
    bool isAddingFromMidiInput;

    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;

    TextEditor midiMessagesBox;
    double startTime;

    int _midiNote;
    bool _noteOn;
};


#endif // MIDI_H
