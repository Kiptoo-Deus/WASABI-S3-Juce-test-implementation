#pragma once

#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
using namespace juce;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    juce::Label clubNameLabel;
    juce::TextEditor clubNameField;
    juce::StringArray countryInitials;
    juce::ComboBox countryComboBox;
    juce::TextButton submitButton;

    // Declare the submitButtonClicked member function
    void submitButtonClicked();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
