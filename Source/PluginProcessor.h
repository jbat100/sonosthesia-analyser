//=======================================================================
/** @file PluginProcessor.h
 *  @brief The top level audio processing class for the Sound Analyser
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

#ifndef __PLUGINPROCESSOR_H_FF438757__
#define __PLUGINPROCESSOR_H_FF438757__

#include "../JuceLibraryCode/JuceHeader.h"

#include "Audio Analysis/AudioAnalysisManager.h"
#include "Audio Analysis/AnalysisModel.h"

#include "Sonosthesia/Target/TargetManager.h"
#include "Sonosthesia/Analysis/AnalysisRelay.h"

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
class SoundAnalyserAudioProcessor : public AudioProcessor, public ValueTree::Listener
{
public:
    //==============================================================================
    SoundAnalyserAudioProcessor();
    ~SoundAnalyserAudioProcessor();

    // === AudioProcessor ===
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;

    int getNumParameters() override;

    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // === ValueTree::Listener ===
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;
    
    //==============================================================================
    
    void refreshFromTree();
    
    ValueTree analyserTree;
    AudioAnalysisManager analyser;
    
    OSCTargetManager& getTargetManager();
    AnalysisRelayManager& getAnalysisRelayManager();
    
private:
    
    OSCTargetManager targetManager;
    AnalysisRelayManager analysisRelayManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundAnalyserAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_FF438757__
