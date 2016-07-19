/*
  ==============================================================================

    AnalysisRelayComponent.cpp
    Created: 8 Jul 2016 2:48:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../Core/Theme.h"
#include "AnalysisRelayComponent.h"


AnalysisSelectorComponent::AnalysisSelectorComponent(SoundAnalyserAudioProcessor& _processor) : processor(_processor)
{
    // just put a combo box inside this component
    addAndMakeVisible (comboBox);
    
    comboBox.addItem ( AnalysisRelay::noIdentifier , identifierGenerator.getNumericIdentifier(AnalysisRelay::noIdentifier) );
    
    for (auto i = processor.analyser.audioAnalyses.begin(); i != processor.analyser.audioAnalyses.end(); i++)
    {
        // can't have 0 as id so we offset by 1
        comboBox.addItem ( (*i)->getName() , identifierGenerator.getNumericIdentifier( (*i)->getIdentifier().toString()) );
    }
    
    // when the combo is changed, we'll get a callback.
    comboBox.addListener (this);
    comboBox.setWantsKeyboardFocus (false);
}

void AnalysisSelectorComponent::resized()
{
    comboBox.setBounds ( getLocalBounds() );
}

void AnalysisSelectorComponent::comboBoxChanged (ComboBox*)
{
    if (relay)
    {
        relay->setAnaysisIdentifier( identifierGenerator.getStringIdentifier(comboBox.getSelectedId()) );
    }
}

void AnalysisSelectorComponent::refresh()
{
    if (relay)
    {
        comboBox.setSelectedId( identifierGenerator.getNumericIdentifier(relay->getAnaysisIdentifier()) );
    }
    else
    {
        comboBox.setSelectedId( identifierGenerator.getNumericIdentifier("None") );
    }
}

void AnalysisSelectorComponent::setRelay(std::shared_ptr<AnalysisRelay> _relay)
{
    relay = _relay;
    refresh();
}


const int AnalysisRelayComponent::desiredHeight = 60;
const int AnalysisRelayComponent::hmargin = 10;
const int AnalysisRelayComponent::vmargin = 4;

//==============================================================================

AnalysisRelayComponent::AnalysisRelayComponent(SoundAnalyserAudioProcessor& _processor) :
    RelayComponent(_processor.getTargetManager()),
    processor(_processor),
    analysisSelectorComponent(_processor)
{
    setOpaque(false);
    
    addAndMakeVisible(analysisLabel);
    analysisLabel.setText("Analysis", dontSendNotification);
    Appearence::theme()->label(analysisLabel);
    
    addAndMakeVisible(analysisSelectorComponent);
    
    addAndMakeVisible(descriptorLabel);
    descriptorLabel.setText("Descriptor", dontSendNotification);
    Appearence::theme()->label(descriptorLabel);
    
    addAndMakeVisible(descriptorField);
    descriptorField.setEditable(false, true, false);
    descriptorField.addListener(this);
    Appearence::theme()->field(descriptorField);
}

AnalysisRelayComponent::~AnalysisRelayComponent()
{
}

void AnalysisRelayComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    Rectangle<float> cellBounds(hmargin, vmargin, b.getWidth() - (hmargin*2), b.getHeight() - (vmargin*2));
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(cellBounds, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(cellBounds.reduced(1), 5);
}

void AnalysisRelayComponent::resized()
{    
    int hspacing = 10;
    int vspacing = 6;
    
    // target   <__________________> analysis _________ | Del |
    // group <_____________> descriptor <_____________> |     |
    
    int targetLabelWidth = 60;
    int analysisLabelWidth = 80;
    int groupLabelWidth = 60;
    int descriptorLabelWidth = 80;
    int buttonWidth = 60;
    int rowHeight = 20;
    
    Rectangle<int> bounds = getBounds();
    
    // double margin, for the outer and inner component cell
    //Rectangle<int> rootBounds = getBounds().reduced(hmargin*4, vmargin*4).translated(hmargin*2, vmargin*2);
    
    int hackyOffset = 10;
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin - hackyOffset, vmargin);
    int fullWidth = rootBounds.getWidth();
    
    // ROW1
    
    int horizontalOffset = rootBounds.getX();
    int verticalOffset = rootBounds.getY();
    
    int flexWidth = (fullWidth - targetLabelWidth - analysisLabelWidth - buttonWidth - (hspacing*4)) / 2;
    
    Rectangle<int> targetLabelBounds(horizontalOffset, verticalOffset, targetLabelWidth, rowHeight);
    horizontalOffset = targetLabelBounds.getRight() + hspacing;
    targetLabel.setBounds(targetLabelBounds);
    
    Rectangle<int> targetSelectorBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = targetSelectorBounds.getRight() + hspacing;
    targetSelectionComponent.setBounds(targetSelectorBounds);
    
    Rectangle<int> analysisLabelBounds(horizontalOffset, verticalOffset, analysisLabelWidth, rowHeight);
    horizontalOffset = analysisLabelBounds.getRight() + hspacing;
    analysisLabel.setBounds(analysisLabelBounds);
    
    Rectangle<int> analysisSelectorBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = analysisSelectorBounds.getRight() + hspacing;
    analysisSelectorComponent.setBounds(analysisSelectorBounds);
    
    // ROW2
    
    horizontalOffset = rootBounds.getX();
    verticalOffset = rootBounds.getY() + vspacing + rowHeight;
    
    flexWidth = (fullWidth - groupLabelWidth - descriptorLabelWidth - buttonWidth - (hspacing*4)) / 2;
    
    Rectangle<int> groupLabelBounds(horizontalOffset, verticalOffset, groupLabelWidth, rowHeight);
    horizontalOffset = groupLabelBounds.getRight() + hspacing;
    groupLabel.setBounds(groupLabelBounds);
    
    Rectangle<int> groupFieldBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = groupFieldBounds.getRight() + hspacing;
    groupField.setBounds(groupFieldBounds);
    
    Rectangle<int> descriptorLabelBounds(horizontalOffset, verticalOffset, descriptorLabelWidth, rowHeight);
    horizontalOffset = descriptorLabelBounds.getRight() + hspacing;
    descriptorLabel.setBounds(descriptorLabelBounds);
    
    Rectangle<int> descriptorFieldBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = descriptorFieldBounds.getRight() + hspacing;
    descriptorField.setBounds(descriptorFieldBounds);
    
    
    // BUTTON
    
    horizontalOffset = rootBounds.getX() + fullWidth - buttonWidth;
    verticalOffset = rootBounds.getY();
    
    //int buttonHeight = (rowHeight * 2) + vspacing; // spans two rows
    Rectangle<int> buttonBounds(horizontalOffset, verticalOffset, buttonWidth, rowHeight);
    deleteButton.setBounds(buttonBounds);
    
}

void AnalysisRelayComponent::refresh()
{
}



void AnalysisRelayComponent::setRelay(std::shared_ptr<Relay> _relay)
{
    std::shared_ptr<AnalysisRelay> analysisRelay = std::dynamic_pointer_cast<AnalysisRelay>(_relay);
    analysisSelectorComponent.setRelay(analysisRelay);
    RelayComponent::setRelay( _relay );
    
    if (analysisRelay)
    {
        descriptorField.setText(analysisRelay->getDescriptor(), dontSendNotification);
    }
    else
    {
        descriptorField.setText("", dontSendNotification);
    }
}

//==============================================================================
AnalysisRelayListComponent::AnalysisRelayListComponent(SoundAnalyserAudioProcessor& _processor) :
    processor(_processor),
    listController("Relay audio analyses to OSC targets")
{
    processor.getAnalysisRelayManager().addChangeListener(this);
    
    setOpaque(false);
    
    addAndMakeVisible(listController);
    listController.add(this);
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(AnalysisRelayComponent::desiredHeight + 10);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
    
}


void AnalysisRelayListComponent::resized()
{
    int controllerHeight = 45;
    int hmargin = 4;
    int vmargin = 4;
    int vspacing = 4;
    
    Rectangle<int> rootBounds = getBounds();
    //Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin, vmargin);
    int verticalOffset = vmargin;
    int width = rootBounds.getWidth();
    
    int listHeight = rootBounds.getHeight() - controllerHeight;
    
    listBox.setBounds( Rectangle<int>(hmargin, vmargin, width, listHeight) );
    verticalOffset = listBox.getBottom() + vspacing;
    
    listController.setBounds( Rectangle<int>(0, verticalOffset, width, controllerHeight) );
}

void AnalysisRelayListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&processor.getAnalysisRelayManager()))
    {
        std::cout << "AnalysisRelayListComponent updating table content on targetManager change\n";
        listBox.updateContent();
    }
}

void AnalysisRelayListComponent::newItemRequest(Component* sender)
{
    processor.getAnalysisRelayManager().newItem();
    listBox.updateContent();
}

void AnalysisRelayListComponent::clearItemsRequest(Component* sender)
{
    processor.getAnalysisRelayManager().clear();
    listBox.updateContent();
}

int AnalysisRelayListComponent::getNumRows()
{
    return processor.getAnalysisRelayManager().getItems().size();
}

void AnalysisRelayListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* AnalysisRelayListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    AnalysisRelayComponent* relayComponent = static_cast<AnalysisRelayComponent*> (existingComponentToUpdate);
    
    std::shared_ptr<AnalysisRelay> relay = nullptr;
    
    if (rowNumber < processor.getAnalysisRelayManager().count())
    {
        relay = processor.getAnalysisRelayManager().getItem(rowNumber);
    }
    
    // If an existing component is being passed-in for updating, we'll re-use it, if not, we'll have to create one.
    if (relayComponent == nullptr)
    {
        relayComponent = new AnalysisRelayComponent(processor);
    }
    
    relayComponent->setRelay(relay);
    return relayComponent;
}

