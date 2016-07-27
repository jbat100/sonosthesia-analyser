/*
  ==============================================================================

    SonosthesiaRootComponent.cpp
    Created: 3 Jul 2016 5:36:44pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "SonosthesiaRootComponent.h"


MainTabbedComponent::MainTabbedComponent(SoundAnalyserAudioProcessor& _processor) :
    TabbedComponent (TabbedButtonBar::TabsAtTop),
    processor(_processor),
    analysisManagerComponent(processor),
    analysisRelayListComponent(processor),
    targetComponent(processor.getTargetManager()),
    settingsComponent(processor)
{
    File applicationFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
    std::cout << "Plugin path : " << applicationFile.getFullPathName() << "\n";
    
    setOpaque(false);
    
    Colour colour = Colours::black.withAlpha(0.3f); // Colour(Colours::black).withAlpha(0.0f);
    
    addTab ("Analysis", colour, &analysisManagerComponent, true);
    addTab ("Relays", colour, &analysisRelayListComponent, true);
    addTab ("Targets", colour, &targetComponent, true);
    addTab ("Settings", colour, &settingsComponent, true);
    
}

void MainTabbedComponent::refreshAnalyses()
{
    analysisManagerComponent.reload();
}

SonosthesiaRootComponent::SonosthesiaRootComponent(SoundAnalyserAudioProcessor& _processor) :
    processor (_processor),
    tabbedComponent(_processor)
{
    setOpaque (true);
    addAndMakeVisible(&tabbedComponent);
}

void SonosthesiaRootComponent::paint (Graphics& g)
{
    Colour dark = Colour(70, 70, 70);
    g.setColour (dark);
    g.fillAll();
}

void SonosthesiaRootComponent::resized()
{
    tabbedComponent.setBounds (getLocalBounds());
}

void SonosthesiaRootComponent::refreshAnalyses()
{
    tabbedComponent.refreshAnalyses();
}
