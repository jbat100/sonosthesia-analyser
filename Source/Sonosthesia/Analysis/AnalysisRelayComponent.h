/*
  ==============================================================================

    AnalysisRelayComponent.h
    Created: 8 Jul 2016 2:48:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSISRELAYCOMPONENT_H_INCLUDED
#define ANALYSISRELAYCOMPONENT_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../../PluginProcessor.h"

//==============================================================================
/*
*/

class AnalysisRelayComponent : public Component
{
public:
    AnalysisRelayComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisRelayComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    SoundAnalyserAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisRelayComponent)
};

class AnalysisRelayListComponent : public Component
{
public:
    AnalysisRelayListComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisRelayListComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisRelayListComponent)
};


#endif  // ANALYSISRELAYCOMPONENT_H_INCLUDED
