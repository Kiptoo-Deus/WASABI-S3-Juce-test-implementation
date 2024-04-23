/*
  ==============================================================================

    AudioPlayerComponent.h
    Created: 23 Apr 2024 3:53:14pm
    Author:  JOEL

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioPlayerComponent : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ChangeListener
{
public:
    AudioPlayerComponent();
    ~AudioPlayerComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void openButtonClicked();
    void playButtonClicked();
    void stopButtonClicked();
    void pauseButtonClicked();
    void sendButtonClicked();

    void changeState(TransportState newState);
    void updateProgressDisplay();

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    juce::TextButton pauseButton;
    juce::TextButton sendButton;
    juce::Slider volumeSlider;
    juce::Label progressLabel;
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::FileChooser> chooser;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    TransportState state;
    juce::TimeSliceThread backgroundThread;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayerComponent)
};
