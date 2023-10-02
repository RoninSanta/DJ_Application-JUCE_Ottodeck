/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 10 Feb 2022 4:19:06am
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
    public:
        //==============================================================================
        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer() override;
        //==============================================================================
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        // Loads the Audio File
        void loadURL(juce::URL audioURL);
        // Sets the Volume of Song
        void setGain(double gain);
        //Set the Speed of the Song
        void setSpeed(double ratio);
        // Set the position of playhead
        void setPosition(double posInSecs);
        //Set relative position of audio file
        void setPositionRelative(double pos);

        //Plays audio file
        void start();
        //Pauses audio file
        void stop();

        /* Get the relative position of the playhead*/
        double getPositionRelative();
        /* Gets the length of transport source in seconds*/
        double getLengthInSeconds();

    private:
        //====================================================================================
        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;
        juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

};