/*
  ==============================================================================

    PlaylistComponent.h
    Created: 11 Feb 2022 2:40:41pm
    Author:  Joseph Shen Fan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Songs.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2,
                      DJAudioPlayer* _playerForParsingMetaData);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(juce::Graphics&, int rowNumber,int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics&, int rowNumber, int columnId,int width, int height, bool rowIsSelected) override;
    

    juce::Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component* existingComponentToUpdate) override;
    void buttonClicked(juce::Button* button) override;

private:
    //==================== IMPORT THE SONGS INTO PLAYLIST ==========================================
    std::vector<Songs> tracks;

    juce::TextButton importButton{ "IMPORT Single/Multiple TRACKS" };
    juce::TextEditor searchField;
    juce::TableListBox library;
    juce::TextButton addToPlayer1Button{ "ADD TO Deck 1" };
    juce::TextButton addToPlayer2Button{ "ADD TO Deck 2" };

    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    DJAudioPlayer* playerForParsingMetaData;
    
    // ================== GET SONG DURATION DETALS ===============================
    juce::String getLength(juce::URL audioURL);
    juce::String secondsToMinutes(double seconds);

    // PLAYLIST FUNCTIONS Eg. Search,Delete and load songs 
    void importToLibrary();
    void searchLibrary(juce::String searchText);
    void saveLibrary();
    void loadLibrary();
    void deleteFromTracks(int id);
    bool isInTracks(juce::String fileNameWithoutExtension);
    int whereInTracks(juce::String searchText);
    void loadInPlayer(DeckGUI* deckGUI);
    /*
    juce::TableListBox tableComponent;
    std::vector<std::string> trackTitles;
    */
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
