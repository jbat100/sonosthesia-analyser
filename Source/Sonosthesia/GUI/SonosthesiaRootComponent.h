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

//==============================================================================
/*
*/
class SonosthesiaRootComponent    : public Component
{
public:
    SonosthesiaRootComponent();
    ~SonosthesiaRootComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SonosthesiaRootComponent)
};


#endif  // SONOSTHESIAROOTCOMPONENT_H_INCLUDED
