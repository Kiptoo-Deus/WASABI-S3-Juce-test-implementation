#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(600, 400);

    // Initialize UI components
    addAndMakeVisible(clubNameLabel);
    clubNameLabel.setText("Club Name:", dontSendNotification);
    addAndMakeVisible(clubNameField);
    // Initialize other UI components similarly
    // Add combo box items
    countryInitials.add("BE");
    countryInitials.add("BG");
    // Add other country initials similarly
    countryComboBox.addItemList(countryInitials, 1);
    addAndMakeVisible(countryComboBox);

    // Set up submit button
    addAndMakeVisible(submitButton);
    submitButton.setButtonText("Submit");
    submitButton.onClick = [this] { submitButtonClicked(); };
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText("Authentication", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // Position UI components
    clubNameLabel.setBounds(20, 20, 100, 20);
    clubNameField.setBounds(130, 20, 150, 20);
    countryComboBox.setBounds(130, 50, 150, 20);
    // Position other UI components similarly
    submitButton.setBounds(130, 80, 100, 30);
}

void MainComponent::submitButtonClicked()
{
    // Handle submit button click event
    String name = clubNameField.getText();
    String region = countryComboBox.getText();
    // Implement authentication logic here
}
