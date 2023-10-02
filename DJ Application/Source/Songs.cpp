/*
  ==============================================================================

    Songs.cpp
    Created: 7 Mar 2022 3:33:48am
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#include "Songs.h"
#include <filesystem>

Songs::Songs(juce::File _file) : file(_file),
title(_file.getFileNameWithoutExtension()),
URL(juce::URL{ _file })
{
    DBG("Created new track with title: " << title);
}

bool Songs::operator==(const juce::String& other) const
{
    return title == other;
}
