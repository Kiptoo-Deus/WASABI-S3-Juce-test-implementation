#pragma once

#include <JuceHeader.h>
#include "AudioPlayerComponent.h" 

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AudioPlayerComponent audioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
