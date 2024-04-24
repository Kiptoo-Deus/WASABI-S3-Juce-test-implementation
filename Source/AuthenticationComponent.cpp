/*
  ==============================================================================

    AuthenticationComponent.cpp
    Created: 23 Apr 2024 2:25:00pm
    Author:  JOEL

  ==============================================================================
*/

#include "AuthenticationComponent.h"
#include "AWS/src/aws-cpp-sdk-core/include/aws/core/Aws.h"
#include "AWS/generated/src/aws-cpp-sdk-s3/include/aws/s3/S3Client.h"

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

//void AuthenticationComponent::submitButtonClicked()
//{
//    if (listener != nullptr)
//        listener->authenticationSubmitted(getClubName(), getRegion());
//}
void AuthenticationComponent::submitButtonClicked()
{
    // Get the club name and region
    juce::String clubName = getClubName();
    juce::String region = getRegion();

    // Initialize AWS credentials and S3 client
    Aws::Auth::AWSCredentials credentials("access_key_id", "secret_key_id");
    Aws::S3::S3Client s3Client(credentials, Aws::Client::ClientConfiguration(), region.toStdString());

    // Prepare S3 object key and content
    std::string bucketName = "your_bucket_name";
    std::string objectKey = clubName.toStdString() + ".txt";
    std::string content = "Club Name: " + clubName.toStdString() + "\nRegion: " + region.toStdString();

    // Perform S3 upload
    Aws::S3::Model::PutObjectRequest request;
    request.WithBucket(bucketName.c_str()).WithKey(objectKey.c_str()).WithBody(Aws::MakeShared<Aws::StringStream>("UploadStream", content));

    auto outcome = s3Client.PutObject(request);
    if (outcome.IsSuccess())
    {
        // Upload successful
        juce::AlertWindow::showMessageBox(juce::AlertWindow::InfoIcon, "Success", "Uploaded to S3 successfully!");
    }
    else
    {
        // Upload failed
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "Failed to upload to S3: " + juce::String(outcome.GetError().GetMessage().c_str()));
    }
}
