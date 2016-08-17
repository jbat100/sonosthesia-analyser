/*
  ==============================================================================

    OriginalPlotComponent.h
    Created: 3 Jul 2016 5:13:47pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ORIGINALPLOTCOMPONENT_H_INCLUDED
#define ORIGINALPLOTCOMPONENT_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class OriginalPlotComponent : public Component, public Timer
{
public:
    OriginalPlotComponent(SoundAnalyserAudioProcessor& _processor);
    ~OriginalPlotComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    // Timer
    void timerCallback() override;

private:
    
    int plotX, plotY, plotHeight;
    
    SoundAnalyserAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OriginalPlotComponent)
};


#endif  // ORIGINALPLOTCOMPONENT_H_INCLUDED
