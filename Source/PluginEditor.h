//=======================================================================
/** @file PluginEditor.h
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

#ifndef __PLUGINEDITOR_H_EA17EABC__
#define __PLUGINEDITOR_H_EA17EABC__

#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"
#include "GUI/OriginalRootComponent.h"
#include "Sonosthesia/GUI/SonosthesiaRootComponent.h"

//==============================================================================
/**
*/
class SoundAnalyserAudioProcessorEditor : public AudioProcessorEditor
{
public:
    
    //==============================================================================
    SoundAnalyserAudioProcessorEditor (SoundAnalyserAudioProcessor* processor);
    ~SoundAnalyserAudioProcessorEditor();
    
    //==============================================================================
    // Component
    void paint (Graphics& g);
    void resized();
    
private:
    
    //OriginalRootComponent rootComponent;
    SonosthesiaRootComponent rootComponent;
    
    SoundAnalyserAudioProcessor* getProcessor() const;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundAnalyserAudioProcessorEditor)
    
};


#endif  // __PLUGINEDITOR_H_EA17EABC__
