#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(600, 400);
    addAndMakeVisible(audioPlayer);
}

MainComponent::~MainComponent() {}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    audioPlayer.setBounds(getLocalBounds());
}
