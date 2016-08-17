/*
  ==============================================================================

    SonosthesiaRootComponent.h
    Created: 3 Jul 2016 5:36:44pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef SONOSTHESIAROOTCOMPONENT_H_INCLUDED
#define SONOSTHESIAROOTCOMPONENT_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../../PluginProcessor.h"

#include "../Target/TargetListComponent.h"
#include "../Analysis/AnalysisRelayComponent.h"
#include "../Analysis/AnalysisManagerComponent.h"

#include "SettingsComponent.h"

//==============================================================================
/*   MainTabbedComponent should be considered private
 */

class MainTabbedComponent : public TabbedComponent
{
    
public:
    
    MainTabbedComponent(SoundAnalyserAudioProcessor& processor);
    
    void refreshAnalyses();
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    
    AnalysisManagerComponent analysisManagerComponent;
    AnalysisRelayListComponent analysisRelayListComponent;
    TargetListComponent targetComponent;
    SettingsComponent settingsComponent;
};

//==============================================================================
/*
*/

class SonosthesiaRootComponent : public Component
{
public:
    SonosthesiaRootComponent(SoundAnalyserAudioProcessor& _processor);
    ~SonosthesiaRootComponent() {}

    void paint (Graphics&) override;
    void resized() override;
    
    void refreshAnalyses();

private:
    
    SoundAnalyserAudioProcessor& processor;
    
    MainTabbedComponent tabbedComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SonosthesiaRootComponent)
};


#endif  // SONOSTHESIAROOTCOMPONENT_H_INCLUDED
