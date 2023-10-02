/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 11 Feb 2022 12:47:20am
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                juce::AudioThumbnailCache& cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse),
                                fileLoaded(false),
                                position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::red);
    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
        g.setColour(juce::Colours::lightgreen);
        g.fillRect(position * getWidth(), 0, 2, getHeight());
        //display name of currently playing track on the waveform in white
        g.setColour(juce::Colours::floralwhite);
        g.setFont(16.0f);
        g.drawText(nowPlaying, getLocalBounds(),
            juce::Justification::centred, true);
    }
    else {
        g.setFont(20.0f);
        g.drawText("File not Loaded...", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        DBG("WaveformDisplay::LOADED!");
        // GET NAME OF SONG and Display on top of wave
        std::string justFile = audioURL.toString(false).toStdString();
        std::size_t startFilePos = justFile.find_last_of("/");
        std::size_t startExtPos = justFile.find_last_of(".");
        std::string extn = justFile.substr(startExtPos + 1, justFile.length() - startExtPos);
        std::string file = justFile.substr(startFilePos + 1, justFile.length() - startFilePos - extn.size() - 2);

        nowPlaying = file;
        repaint();
    }
    else {
        DBG("WaveformDisplay::NOT!");
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    DBG("WaveformDisplay::CHANGE RECEIVED!");
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && pos==pos)
    {
        position = pos;
        repaint();
    }
}

void WaveformDisplay::resized()
{
}
