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
class AnalysisManagerComponent    : public Component,
                                    public Button::Listener,
                                    public ValueTree::Listener,
                                    public Label::Listener,
                                    public ComboBox::Listener
{
public:
    
    AnalysisManagerComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisManagerComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    //==============================================================================
    // Button::Listener
    void buttonClicked (Button* button) override;
    
    //==============================================================================
    // ValueTree::Listener
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;
    
    //==============================================================================
    // Label::Listener
    void labelTextChanged (Label* labelThatHasChanged) override;
    
    //==============================================================================
    // ComboBox::Listener
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    //==============================================================================
    void textEditorTextChanged (TextEditor& textEditor);
    
    //==============================================================================
    
    void setValueTree (ValueTree tree);
    void addAnalysis (ValueTree& analysisTree);
    void refreshFromTree();
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    
    int getBufferSizeFromIndex(int index);
    int getIndexFromBufferSize(int bufferSize);
    double round(double val) { return floor(val + 0.5); }
    
    OwnedArray<Component> analysisComponents;
    
    TextButton newAnalysisButton;
    
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisManagerComponent)
};


#endif  // ANALYSISMANAGERCOMPONENT_H_INCLUDED
