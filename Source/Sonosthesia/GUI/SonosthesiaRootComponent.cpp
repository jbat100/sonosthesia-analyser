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
analysisRelayComponent(processor),
targetComponent(processor.getTargetManager())
{
    File applicationFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
    std::cout << "Plugin path : " << applicationFile.getFullPathName() << "\n";
    
    setOpaque(false);
    
    Colour colour = Colours::black.withAlpha(0.3f); // Colour(Colours::black).withAlpha(0.0f);
    
    addTab ("Analysis", colour, &analysisManagerComponent, true);
    addTab ("Relay", colour, &analysisRelayComponent, true);
    addTab ("Targets", colour, &targetComponent, true);
    
}

SonosthesiaRootComponent::SonosthesiaRootComponent(SoundAnalyserAudioProcessor& _processor) :
    processor (_processor),
    tabbedComponent(_processor)
{
    setOpaque (true);
    
    
    addAndMakeVisible(&tabbedComponent);
    
    //addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    //resizeLimits.setSizeLimits (150, 150, 1000, 500);
    
    //std::cout << "Editor setting UI dimensions to processor setting " << processor.lastUIWidth << " " << processor.lastUIHeight << "\n";
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //setSize (processor.lastUIWidth, processor.lastUIHeight);
}

void SonosthesiaRootComponent::paint (Graphics& g)
{
    Colour dark = Colour(70, 70, 70);
    
    g.setColour (dark);
    
    /*
     File applicationFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
     File imageFile = applicationFile.getChildFile("Contents/Resources/space-dense.png");
     Image image = ImageCache::getFromFile(imageFile);
     g.setTiledImageFill (image, 0, 0, 1.0);
     */
    
    g.fillAll();
}

void SonosthesiaRootComponent::resized()
{
    tabbedComponent.setBounds (getLocalBounds());

}
