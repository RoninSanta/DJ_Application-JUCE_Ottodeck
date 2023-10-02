/*
  ==============================================================================

    Songs.h
    Created: 7 Mar 2022 3:33:48am
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Songs
{
    public:
        Songs(juce::File _file);
        juce::File file;
        juce::URL URL;
        juce::String title;
        juce::String length;
        /**objects are compared by title*/
        bool operator==(const juce::String& other) const;
};
