//=======================================================================
/** @file SimpleAnalysisComponent.h
 *  @brief The basic component for an audio analysis module. Can be extended
 * to create custom components
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
//=======================================================================

#ifndef __Gluver__MappingComponent__
#define __Gluver__MappingComponent__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Audio Analysis/AnalysisModel.h"
#include "../Audio Analysis/AudioAnalysis.h"

/** 
 A generic GUI component for AudioAnalysis modules.
 Extend this class to create a custom component.
*/

class SimpleAnalysisComponent : public Component, public Button::Listener, AudioAnalysisListener
{
    
public:
    
    SimpleAnalysisComponent(AudioAnalysis* _analysis);
    
    virtual ~SimpleAnalysisComponent() {}
    
    //void refreshFromTree();
    
    void reload();
    
    //======================================================================
    // Component
    void resized() override;
    void paint(Graphics& g) override;
    
    //======================================================================
    // Button::Listener
    void buttonClicked (Button* button) override;
    
    //======================================================================
    // AudioAnalysisListener
    
    void audioAnalysisChanged(AudioAnalysis* analysis) override;
    
    static const int yOffset;
    
protected:
    
    //ValueTree analysisTree;
    
    AudioAnalysis* analysis;
    
private:
    
    Label nameLabel;
    Label activityIndicator;
    
    void updateActivityIndicator();
    
    //TextButton sendButton;
    //TextButton plotButton;
    //TextButton removeButton;
    
    //======================================================================//
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleAnalysisComponent)
    //======================================================================//
};

#endif /* defined(__Gluver__MappingComponent__) */
