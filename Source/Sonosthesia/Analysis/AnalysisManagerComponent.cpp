/*
  ==============================================================================

    AnalysisManagerComponent.cpp
    Created: 5 Jul 2016 9:52:44pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "AnalysisManagerComponent.h"

#include "../../Audio Analysis/AnalysisModel.h"
#include "../../PluginProcessor.h"

#include "SimpleAnalysisComponent.h"
#include "AnalysisSelectionComponent.h"

//==============================================================================
AnalysisManagerComponent::AnalysisManagerComponent(SoundAnalyserAudioProcessor& _processor) : processor(_processor)
{
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);
    
    //newAnalysisButton.setButtonText("+");
    //addAndMakeVisible(&newAnalysisButton);
    //newAnalysisButton.addListener(this);
    //refreshFromTree();
    
    setOpaque(false);
    
    //addAndMakeVisible(listController);
    //listController.add(this);
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(34);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
    
    //oscTargetManager.addChangeListener(this);
    
}

AnalysisManagerComponent::~AnalysisManagerComponent()
{
}

void AnalysisManagerComponent::paint (Graphics& g)
{
    
}


/*==============================================================================
void AnalysisManagerComponent::refreshFromTree()
{
    analysisComponents.clear();
    
    for (int i = 0;i < processor.analyserTree.getNumChildren();i++)
    {
        ValueTree analysisTree = processor.analyserTree.getChild(i);
        addAnalysis(analysisTree);
    }
    
    resized();
}
*/

//==============================================================================
/*
void AnalysisManagerComponent::buttonClicked (Button* button)
{
    if (button == &newAnalysisButton)
    {
        AlertWindow w ("Add new analysis..",
                       "Please slect a new device from the list below",
                       AlertWindow::NoIcon);
        
        ScopedPointer<AnalysisSelectionComponent> analysisSelector;
        
        analysisSelector = new AnalysisSelectionComponent(processor.analyserTree, &processor.analyser);
        
        w.addCustomComponent(analysisSelector);
        
        w.addButton ("ok",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        w.setColour(AlertWindow::ColourIds::backgroundColourId, Colours::lightgrey);
        
        if (w.runModalLoop() != 0) // if they picked 'ok'
        {
            const int optionIndexChosen = analysisSelector->getSelectedAnalysis();
            
            if (optionIndexChosen >= 0)
            {
                AudioAnalysis *chosenAnalysis = processor.analyser.audioAnalyses[optionIndexChosen];
                AnalysisModel::addNewAnalysis(processor.analyserTree, chosenAnalysis->createAnalysisTree());
            }
        }
    }
}
 */


/*==============================================================================
void AnalysisManagerComponent::addAnalysis(ValueTree& analysisTree)
{
    
    for (int i = 0;i < processor.analyser.audioAnalyses.size();i++)
    {
        if (analysisTree.getType() == processor.analyser.audioAnalyses[i]->getIdentifier())
        {
            analysisComponents.add(processor.analyser.audioAnalyses[i]->getGUIComponent(analysisTree));
            
        }
    }
    
    addChildComponent(analysisComponents.getLast());
    analysisComponents.getLast()->setVisible(true);
    
    resized();
}
*/



void AnalysisManagerComponent::resized()
{
    listBox.setBounds( getBounds() );
}



int AnalysisManagerComponent::getNumRows()
{
    return processor.analyser.audioAnalyses.size();
}

void AnalysisManagerComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* AnalysisManagerComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    Component* component = existingComponentToUpdate;
    
    AudioAnalysis* analysis = processor.analyser.audioAnalyses[rowNumber];
    
    // If an existing component is being passed-in for updating, we'll re-use it, but
    // if not, we'll have to create one.
    if (component == nullptr && analysis)
    {
        ValueTree dummy; // this is used to transfer state, but the GUI doing that seems wrong to me...
        component = analysis->getGUIComponent(dummy);
    }
    
    return component;
}

void AnalysisManagerComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    
}

