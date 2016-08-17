//=======================================================================
/** @file PluginEditor.cpp
 *  @brief The top level GUI class for the Sound Analyser
 *  @author Adam Stark
 *  @copyright Copyright (C) 2014  Adam Stark
 *
 * This file is part of Sound Analyser.
 *
 * Sound Analyser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sound Analyser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sound Analyser.  If not, see <http://www.gnu.org/licenses/>.
 */
//======================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "../JuceLibraryCode/BinaryData.h"


//==============================================================================
SoundAnalyserAudioProcessorEditor::SoundAnalyserAudioProcessorEditor (SoundAnalyserAudioProcessor* processor) :
    AudioProcessorEditor (processor),
    rootComponent(*processor)
{
    processor->getAnalysisRelayManager().addChangeListener(this);
    
    // This is where our plugin's editor size is set.
    setSize (600, 600);
    
    addAndMakeVisible(rootComponent);

    updateAnalysisRelayListeners();
    updateAnalysisRelayFlags();
    rootComponent.refreshAnalyses();
}



//==============================================================================
SoundAnalyserAudioProcessorEditor::~SoundAnalyserAudioProcessorEditor()
{
    
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::paint (Graphics& g)
{
    
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::resized()
{
    rootComponent.setBounds( getLocalBounds() );
}

//==============================================================================
SoundAnalyserAudioProcessor* SoundAnalyserAudioProcessorEditor::getProcessor() const
{
    return static_cast <SoundAnalyserAudioProcessor*> (getAudioProcessor());
}


void SoundAnalyserAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &getProcessor()->getAnalysisRelayManager())
    {
        updateAnalysisRelayListeners();
        updateAnalysisRelayFlags();
        rootComponent.refreshAnalyses();
    }
}

void SoundAnalyserAudioProcessorEditor::analysisRelayChanged(AnalysisRelay* relay)
{
    updateAnalysisRelayFlags();
    rootComponent.refreshAnalyses();
}

void SoundAnalyserAudioProcessorEditor::analysisRelayInvalidated(AnalysisRelay* relay)
{
    updateAnalysisRelayFlags();
    rootComponent.refreshAnalyses();
}

void SoundAnalyserAudioProcessorEditor::updateAnalysisRelayListeners()
{
    auto relays = getProcessor()->getAnalysisRelayManager().getItems();
    for (auto i = relays.begin(); i != relays.end(); ++i)
    {
        (*i)->add(this);
    }
}

void SoundAnalyserAudioProcessorEditor::updateAnalysisRelayFlags()
{
    std::cout << "SoundAnalyserAudioProcessor updateAnalysisRelayFlags\n";
    
    // for each analysis check whether a relay is referring to it, if so, mark it as relayed
    for (auto i = getProcessor()->analyser.audioAnalyses.begin(); i != getProcessor()->analyser.audioAnalyses.end(); ++i)
    {
        AudioAnalysis* analysis = (*i);
        if (getProcessor()->getAnalysisRelayManager().analysisIsRelayed( analysis->getIdentifier().toString() ))
        {
            analysis->setRelayed(true);
            std::cout << "SoundAnalyserAudioProcessor " << analysis->getIdentifier().toString() << " is relayed\n";
        }
        else
        {
            analysis->setRelayed(false);
            std::cout << "SoundAnalyserAudioProcessor " << analysis->getIdentifier().toString() << " is not relayed\n";
        }
    }
}

