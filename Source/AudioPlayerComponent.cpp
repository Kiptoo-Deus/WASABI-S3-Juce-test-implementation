/*
  ==============================================================================

    AudioPlayerComponent.cpp
    Created: 23 Apr 2024 3:53:14pm
    Author:  JOEL

  ==============================================================================
*/

#include "AudioPlayerComponent.h"

AudioPlayerComponent::AudioPlayerComponent()
    : state(Stopped),
    backgroundThread("AudioPlayerThread"),
    formatManager(),
    transportSource(),
    readerSource(nullptr)
{
    // Set up open button
    addAndMakeVisible(openButton);
    openButton.setButtonText("Open...");
    openButton.onClick = [this] { openButtonClicked(); };

    // Set up play button
    addAndMakeVisible(playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setEnabled(false);

    // Set up stop button
    addAndMakeVisible(stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setEnabled(false);

    // Set up pause button
    addAndMakeVisible(pauseButton);
    pauseButton.setButtonText("Pause");
    pauseButton.onClick = [this] { pauseButtonClicked(); };
    pauseButton.setEnabled(false);

    // Set up send button
    addAndMakeVisible(sendButton);
    sendButton.setButtonText("Send");
    sendButton.onClick = [this] { sendButtonClicked(); };
    sendButton.setEnabled(false);

    // Set up volume slider
    addAndMakeVisible(volumeSlider);
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);

    // Set up progress label
    addAndMakeVisible(progressLabel);
    progressLabel.setJustificationType(juce::Justification::centred);
    progressLabel.setFont(juce::Font(15.0f));

    // Set up format manager and transport source
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
    backgroundThread.startThread();
}

AudioPlayerComponent::~AudioPlayerComponent() {}

void AudioPlayerComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AudioPlayerComponent::resized()
{
    auto bounds = getLocalBounds();
    auto buttonWidth = bounds.getWidth() / 5;
    auto buttonHeight = bounds.getHeight() / 2;

    // Position buttons and slider
    openButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    playButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    stopButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    pauseButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    sendButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    volumeSlider.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));

    // Position progress label
    progressLabel.setBounds(bounds.reduced(5));
}

void AudioPlayerComponent::buttonClicked(juce::Button* button)
{
    if (button == &openButton)
    {
        openButtonClicked();
    }
    else if (button == &playButton)
    {
        playButtonClicked();
    }
    else if (button == &stopButton)
    {
        stopButtonClicked();
    }
    else if (button == &pauseButton)
    {
        pauseButtonClicked();
    }
    else if (button == &sendButton)
    {
        sendButtonClicked();
    }
}

void AudioPlayerComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        transportSource.setGain(volumeSlider.getValue());
    }
}

void AudioPlayerComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            changeState(Playing);
        }
        else if (state == Stopping || state == Playing)
        {
            changeState(Stopped);
        }
        else if (state == Pausing)
        {
            changeState(Paused);
        }

        updateProgressDisplay();
    }
}

void AudioPlayerComponent::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser>("Select an audio file to play...",
        juce::File{},
        "*.wav;*.mp3;*.ogg");
    auto chooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

    if (file.existsAsFile())
    {
        auto* reader = formatManager.createReaderFor(file);

        if (reader != nullptr)
        {
            auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            playButton.setEnabled(true);
            stopButton.setEnabled(true);
            pauseButton.setEnabled(true);
            sendButton.setEnabled(true);
            readerSource.reset(newSource.release());
            changeState(Starting);

            // Start playback
            transportSource.start();
        }
    }
        });
}

void AudioPlayerComponent::playButtonClicked()
{
    if (state == Stopped || state == Paused)
    {
        changeState(Starting);
    }
    else if (state == Playing)
    {
        changeState(Pausing);
    }
}

void AudioPlayerComponent::stopButtonClicked()
{
    if (state == Paused)
    {
        changeState(Stopped);
    }
    else
    {
        changeState(Stopping);
    }
}

void AudioPlayerComponent::pauseButtonClicked()
{
    if (state == Playing)
    {
        changeState(Pausing);
    }
}

void AudioPlayerComponent::sendButtonClicked()
{
    // Implement sending audio file to S3 bucket
}

void AudioPlayerComponent::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            transportSource.stop();
            transportSource.setPosition(0.0);
            playButton.setButtonText("Play");
            break;

        case Starting:
            playButton.setButtonText("Pause");
            transportSource.start();
            break;

        case Playing:
            playButton.setButtonText("Pause");
            break;

        case Pausing:
            transportSource.stop();
            break;

        case Paused:
            playButton.setButtonText("Resume");
            break;

        case Stopping:
            transportSource.stop();
            break;
        }
    }
}

void AudioPlayerComponent::updateProgressDisplay()
{
    auto duration = transportSource.getLengthInSeconds();
    auto position = transportSource.getCurrentPosition();
    auto progress = position / duration * 100.0;
    progressLabel.setText(juce::String(progress, 1) + "%", juce::dontSendNotification);
}
