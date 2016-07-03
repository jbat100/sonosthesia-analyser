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
#include "Audio Analysis/AnalysisModel.h"
#include "GUI/PluginLookAndFeel.h"
#include "GUI/SimpleAnalysisComponent.h"
#include "GUI/AnalysisSelectionComponent.h"

enum BufferSizeValues
{
    BufferSize64,
    BufferSize128,
    BufferSize256,
    BufferSize512,
    BufferSize1024,
    BufferSize2048,
    BufferSize4096,
    NumBufferSizes
};


//==============================================================================
/**
*/
class SoundAnalyserAudioProcessorEditor :   public AudioProcessorEditor,
                                            public Button::Listener,
                                            public Timer,
                                            public ValueTree::Listener,
                                            public Label::Listener,
                                            public ComboBox::Listener
{
public:
    
    //==============================================================================
    SoundAnalyserAudioProcessorEditor (SoundAnalyserAudioProcessor* ownerFilter, ValueTree analyserTree_);
    ~SoundAnalyserAudioProcessorEditor();
    
    //==============================================================================
    void setValueTree (ValueTree tree);
    
    void refreshFromTree();
    
    void addAnalysis (ValueTree& analysisTree);
    
    //==============================================================================
    // Component
    void paint (Graphics& g);
    void resized();
    
    //==============================================================================
    // Button::Listener
    void buttonClicked (Button* button);
    
    //==============================================================================
    // Timer
    void timerCallback();
    
    //==============================================================================
    // ValueTree::Listener
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property);
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved);
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex);
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged);
    
    //==============================================================================
    // Label::Listener
    void labelTextChanged (Label* labelThatHasChanged);
    
    //==============================================================================
    // ComboBox::Listener
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    
    //==============================================================================
    void textEditorTextChanged (TextEditor& textEditor);
    
private:
    
    int getBufferSizeFromIndex(int index);
    
    int getIndexFromBufferSize(int bufferSize);
    
    SoundAnalyserAudioProcessor* getProcessor() const;
    
	double round(double val)
	{
		return floor(val + 0.5);
	}

    ValueTree analyserTree;
    
    OwnedArray<Component> analysisComponents;
    
    TextButton newAnalysisButton;
    
    int plotX, plotY, plotHeight;
    
    Label analyserId;
    
    
    Label OSCPort;
    Label OSCPortText;
    
    Label IPAddressValue;
    Label IPAddressText;
    
    Label analyserIdText;
    
    
    Label bufferSizeText;
    Label bufferSizeValue;
    
    ComboBox bufferSizeComboBox;
    
    Label pluginTitleLabel;
    Label pluginVersionLabel;
    
    PluginLookAndFeel pluginLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundAnalyserAudioProcessorEditor)
    
};


#endif  // __PLUGINEDITOR_H_EA17EABC__
