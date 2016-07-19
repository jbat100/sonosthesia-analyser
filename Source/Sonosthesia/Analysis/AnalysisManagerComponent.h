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
#include "../../PluginProcessor.h"
#include "PluginLookAndFeel.h"

//==============================================================================
/*
*/
class AnalysisManagerComponent : public Component, public ListBoxModel, public ChangeListener
{
public:
    
    AnalysisManagerComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisManagerComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    // ======= ChangeListener ===========
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    //OwnedArray<Component> analysisComponents;
    
    ListBox listBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisManagerComponent)
};


#endif  // ANALYSISMANAGERCOMPONENT_H_INCLUDED
