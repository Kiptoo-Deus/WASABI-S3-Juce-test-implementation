/*
  ==============================================================================

    AuthenticationListener.h
    Created: 23 Apr 2024 2:32:48pm
    Author:  JOEL

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AuthenticationListener
{
public:
    virtual ~AuthenticationListener() = default;
    virtual void authenticationSubmitted(const juce::String& clubName, const juce::String& region) = 0;
};
