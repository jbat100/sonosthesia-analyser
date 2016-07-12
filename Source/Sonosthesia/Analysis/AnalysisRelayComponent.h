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
#include "../Core/ListControllerComponent.h"
#include "../Relay/RelayComponent.h"


class AnalysisSelectorComponent : public Component, private ComboBoxListener
{
public:
    
    AnalysisSelectorComponent (SoundAnalyserAudioProcessor& _processor);
    virtual ~AnalysisSelectorComponent() {}
    
    void setRelay(std::shared_ptr<AnalysisRelay> _relay);
    
    void refresh();
    
    // ======== Component ==========
    
    virtual void resized() override;
    
    // ===== ComboBoxListener ======
    
    virtual void comboBoxChanged (ComboBox*) override;
    
private:
    
    NumericIdentifierGenerator identifierGenerator;
    ComboBox comboBox;
    
    std::shared_ptr<AnalysisRelay> relay;
    SoundAnalyserAudioProcessor& processor;
};


//==============================================================================
/*
*/

class AnalysisRelayComponent : public RelayComponent
{
public:
    AnalysisRelayComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisRelayComponent();

    void paint (Graphics&) override;
    void resized() override;

    virtual void setRelay(std::shared_ptr<Relay> _relay) override;
    
    static const int desiredHeight;
    static const int hmargin;
    static const int vmargin;
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    
    std::shared_ptr<AnalysisRelay> relay;
    
    Label descriptorLabel;
    Label descriptorField;
    
    Label analysisLabel;
    AnalysisSelectorComponent analysisSelectorComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisRelayComponent)
};

//==============================================================================
/*
 */

class AnalysisRelayListComponent : public Component, public ListBoxModel, public ChangeListener, public ListControllerListener
{
public:
    AnalysisRelayListComponent(SoundAnalyserAudioProcessor& _processor);
    ~AnalysisRelayListComponent() {}
    
    void resized() override;
    
    // ======= ChangeListener ===========
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    // ======== ListControllerListener ===========
    
    virtual void newItemRequest(Component* sender) override;
    virtual void clearItemsRequest(Component* sender) override;
    
private:
    
    SoundAnalyserAudioProcessor& processor;
    
    ListControllerComponent listController;
    ListBox listBox;
    Font font;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisRelayListComponent)
};


#endif  // ANALYSISRELAYCOMPONENT_H_INCLUDED
