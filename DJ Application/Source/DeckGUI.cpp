/*
  ==============================================================================

    DeckGUI.cpp
    Created: 10 Feb 2022 5:11:10pm
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse) : player(_player),
                                                          waveformDisplay(formatManagerToUse, cacheToUse)
{
    // initialise any special settings that your component needs.
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(VolSlider);
    addAndMakeVisible(VolLabel);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    VolSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    //set colour scheme for sliders 
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::mediumspringgreen); //dial
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::lightslategrey); //body
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightslategrey); //body

    VolSlider.setRange(0.0, 1.0);
    VolSlider.setNumDecimalPlacesToDisplay(2);
    VolSlider.setValue(0.5); //default volume half of max vol
    VolSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    VolSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    //============= LABELS =========================
    VolLabel.setText("Volume", juce::dontSendNotification);
    VolLabel.attachToComponent(&VolSlider, false);
    VolLabel.setJustificationType(juce::Justification::centred);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);
    speedLabel.setJustificationType(juce::Justification::centred);

    //=================== SPEED SLIDER  ===============================
    speedSlider.setRange(0.0, 30.0);  // Set Max Speed 30x
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalDrag);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    speedSlider.setMouseDragSensitivity(120);
    //===================== POSITION SLIDER ========================
    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    posSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        DBG("PLAY Button was Clicked");
        player->start();
    }
    if (button == &stopButton)
    {
        DBG("STOP Button was Clicked");
        player->stop();
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select an audio file..."};
        //browseForFileToOpen() is removed in the latest update of JUCE have to edit the projucer app to get it to work
        if (chooser.browseForFileToOpen())
        {   //Load the URL
            player->loadURL(juce::URL{chooser.getResult()});
            //Display the waveforms
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &VolSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}
bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile called");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
    DBG("DeckGUI::filesDropped");
    if (files.size() == 1)
    {
        player->loadURL(juce::URL{ juce::File{files[0]}});
    }
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 6;
    double colW = getWidth() / 4;
    
    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 2);

    posSlider.setBounds(0, rowH * 2, getWidth(), rowH);

    VolSlider.setBounds(colW + 10 , rowH * 3 +10 , colW/ 2, rowH * 2 - 10) ;
    speedSlider.setBounds(colW*2 , rowH * 3 + 10, colW*2, rowH * 2);

    playButton.setBounds(colW/8 + 10, rowH * 5 + 10, colW - 10 , rowH - 20);
    stopButton.setBounds(colW + 30 , rowH * 5 + 10, colW - 10, rowH - 20);
    loadButton.setBounds(colW*2 + 40 , rowH * 5 + 10, colW + 10, rowH - 20);
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}
