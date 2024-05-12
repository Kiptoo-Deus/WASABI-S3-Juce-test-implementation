/*
  ==============================================================================

    AuthenticationComponent.cpp
    Created: 23 Apr 2024 2:25:00pm
    Author:  JOEL

  ==============================================================================
*/

#include "AuthenticationComponent.h"


AuthenticationComponent::AuthenticationComponent()
{
    setSize(600, 400);

    // Initialize UI components for authentication screen
    addAndMakeVisible(clubNameLabel);
    clubNameLabel.setText("Club Name:", juce::dontSendNotification);
    addAndMakeVisible(clubNameField);
    // Initialize other UI components similarly
    // Add combo box items
    countryInitials.add("BE");
    countryInitials.add("BG");
    countryInitials.add("BE");
    countryInitials.add("BG");
    countryInitials.add("CZ");
    countryInitials.add("DK");
    countryInitials.add("DE");
    countryInitials.add("EE");
    countryInitials.add("IE");
    countryInitials.add("EL");
    countryInitials.add("ES");
    countryInitials.add("FR");
    countryInitials.add("HR");
    countryInitials.add("IT");
    countryInitials.add("CY");
    countryInitials.add("LV");
    countryInitials.add("LT");
    countryInitials.add("LU");
    countryInitials.add("HU");
    countryInitials.add("MT");
    countryInitials.add("NL");
    countryInitials.add("AT");
    countryInitials.add("PL");
    countryInitials.add("PT");
    countryInitials.add("RO");
    countryInitials.add("SI");
    countryInitials.add("SK");
    countryInitials.add("FI");
    countryInitials.add("SE");
    countryInitials.add("IS");
    countryInitials.add("LI");
    countryInitials.add("NO");
    countryInitials.add("CH");
    countryInitials.add("UK");

    // Add other country initials similarly
    countryComboBox.addItemList(countryInitials, 1);
    addAndMakeVisible(countryComboBox);

    // Set up submit button
    addAndMakeVisible(submitButton);
    submitButton.setButtonText("Submit");
    submitButton.onClick = [this] { submitButtonClicked(); };
}

AuthenticationComponent::~AuthenticationComponent() {}

void AuthenticationComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Authentication", getLocalBounds(), juce::Justification::centred, true);
}

void AuthenticationComponent::resized()
{
    // Position UI components
    clubNameLabel.setBounds(20, 20, 100, 20);
    clubNameField.setBounds(130, 20, 150, 20);
    countryComboBox.setBounds(130, 50, 150, 20);

    submitButton.setBounds(130, 80, 100, 30);
}

void AuthenticationComponent::setListener(AuthenticationListener* listener)
{
    this->listener = listener;
}

juce::TextButton& AuthenticationComponent::getSubmitButton()
{
    return submitButton;
}

juce::String AuthenticationComponent::getClubName() const
{
    return clubNameField.getText();
}

juce::String AuthenticationComponent::getRegion() const
{
    return countryComboBox.getText();
}

void AuthenticationComponent::submitButtonClicked()
{
  if (listener != nullptr)
       listener->authenticationSubmitted(getClubName(), getRegion());
}
