/*
  ==============================================================================

    DeckGUI.h
    Created: 10 Feb 2022 5:11:10pm
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    /**Rescaling of components on the application window*/
    void resized() override;

    /** implement Button::Listner*/
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listner*/
    void sliderValueChanged(juce::Slider*) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    /*To allow call back for updating waveform visual*/
    void timerCallback() override;

private:

    //================ BUTTONS ==========================================
    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "Choose File..." };
    juce::Slider VolSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    //================== LABELS =====================================
    juce::Label VolLabel;
    juce::Label speedLabel;

    //Change Colour Scheme of SLiders
    juce::LookAndFeel_V4 lookandfeel;

    void loadFile(juce::URL audioURL);
    DJAudioPlayer* player;
    //Create waveform visual
    WaveformDisplay waveformDisplay;
    juce::SharedResourcePointer< juce::TooltipWindow > sharedTooltip;

    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
