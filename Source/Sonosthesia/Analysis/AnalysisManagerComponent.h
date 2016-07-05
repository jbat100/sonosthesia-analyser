/*
  ==============================================================================

    AnalysisManagerComponent.h
    Created: 5 Jul 2016 9:52:44pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSISMANAGERCOMPONENT_H_INCLUDED
#define ANALYSISMANAGERCOMPONENT_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AnalysisManagerComponent    : public Component
{
public:
    AnalysisManagerComponent();
    ~AnalysisManagerComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisManagerComponent)
};


#endif  // ANALYSISMANAGERCOMPONENT_H_INCLUDED
