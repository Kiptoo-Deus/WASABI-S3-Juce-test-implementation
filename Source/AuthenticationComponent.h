/*
  ==============================================================================

    AuthenticationComponent.h
    Created: 23 Apr 2024 2:25:00pm
    Author:  JOEL

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AuthenticationListener.h"

class AuthenticationComponent : public juce::Component
{
public:
    AuthenticationComponent();
    ~AuthenticationComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setListener(AuthenticationListener* listener);

    juce::TextButton& getSubmitButton();
    juce::String getClubName() const;
    juce::String getRegion() const;

private:
    void submitButtonClicked();

    juce::Label clubNameLabel;
    juce::TextEditor clubNameField;
    juce::StringArray countryInitials;
    juce::ComboBox countryComboBox;
    juce::TextButton submitButton;

    AuthenticationListener* listener = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AuthenticationComponent)
};
