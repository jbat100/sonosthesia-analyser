/*
  ==============================================================================

    RelayComponent.cpp
    Created: 16 May 2016 4:07:30pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "RelayComponent.h"
#include "Theme.h"

const int TargetSelectionComponent::noSelection = -1;
const String TargetSelectionComponent::noSelectionText = "None";

TargetSelectionComponent::TargetSelectionComponent (OSCTargetManager& _manager) : manager(_manager)
{
    addAndMakeVisible (comboBox);
    
    manager.addChangeListener(this);
    
    listenToAllTargets();
    
    comboBox.setTextWhenNothingSelected("None");
    comboBox.addListener (this);
    comboBox.setWantsKeyboardFocus (false);
}

void TargetSelectionComponent::resized()
{
    //comboBox.setBoundsInset (BorderSize<int> (2));
    
    comboBox.setBounds( getLocalBounds() );
}

void TargetSelectionComponent::refresh()
{
    updateComboBox();
}

void TargetSelectionComponent::setRelay (std::shared_ptr<Relay> _relay)
{
    relay = _relay;
    if (relay)
    {
        std::shared_ptr<OSCTarget> target = relay->getTarget();
        if (target)
        {
            int numericIdentifier = generator.getNumericIdentifier(target->getIdentifier());
            comboBox.setSelectedId (numericIdentifier, dontSendNotification);
            return;
        }
        else
        {
            comboBox.setSelectedId (noSelection, dontSendNotification);
        }
    }
    else
    {
        comboBox.setSelectedId (noSelection, dontSendNotification);
    }
}

void TargetSelectionComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == dynamic_cast<ChangeBroadcaster*>(&manager))
    {
        listenToAllTargets();
        updateComboBox();
    }
}

void TargetSelectionComponent::targetInvalidated(OSCTarget* target)
{
    updateComboBox();
}

void TargetSelectionComponent::targetChanged(OSCTarget* target)
{
    updateComboBox();
}

void TargetSelectionComponent::comboBoxChanged (ComboBox*)
{
    try
    {
        if (relay)
        {
            int numericIdentifier = comboBox.getSelectedId();
            if (numericIdentifier == noSelection)
            {
                relay->setTarget (nullptr);
            }
            else if (numericIdentifier > 0)
            {
                String identifier = generator.getStringIdentifier(numericIdentifier);
                std::shared_ptr<OSCTarget> target = manager.getItem(identifier);
                relay->setTarget (target);
            }
        }
    }
    catch (std::invalid_argument& err)
    {
        std::cerr << "TargetColumnCustomComponent comboBoxChanged exception: " << &err << "\n";
    }
    
}


void TargetSelectionComponent::listenToAllTargets()
{
    auto targets = manager.getItems();
    // whenever a target changes we want to update the combo box to reflect the changes
    // perhaps overkill, but better safe than inconsistant...
    for (auto i = targets.begin(); i != targets.end(); i++)
    {
        (*i)->add(this);
    }
}

void TargetSelectionComponent::updateComboBox()
{
    
    const std::vector< std::shared_ptr<OSCTarget> > targets = manager.getItems();
    
    comboBox.clear();
    
    comboBox.addItem(noSelectionText, noSelection);
    
    for (auto i = targets.begin(); i != targets.end(); i++)
    {
        int numericIdentifier = generator.getNumericIdentifier( (*i)->getIdentifier() );
        String description = (*i)->getHostName() + ":" + String((*i)->getPortNumber());
        comboBox.addItem(description, numericIdentifier);
    }
    
    setRelay(relay);
    
}




RelayComponent::RelayComponent(OSCTargetManager& _targetManager) :
targetManager(_targetManager),
    targetSelectionComponent(_targetManager)
{
    setOpaque(false);
    
    addAndMakeVisible(groupLabel);
    groupLabel.setText("Group", dontSendNotification);
    Appearence::theme()->label(groupLabel);
    
    addAndMakeVisible(groupField);
    groupField.setEditable(false, true, false);
    groupField.addListener(this);
    Appearence::theme()->field(groupField);
    
    addAndMakeVisible(targetLabel);
    targetLabel.setText("Target", dontSendNotification);
    Appearence::theme()->label(targetLabel);
    
    addAndMakeVisible(targetSelectionComponent);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setButtonText("Delete");
    Appearence::theme()->textButton(deleteButton);
}

void RelayComponent::setRelay(std::shared_ptr<Relay> _relay)
{
    targetSelectionComponent.setRelay(_relay);
    relay = _relay;
    refresh();
}

std::shared_ptr<Relay> RelayComponent::getRelay()
{
    return relay;
}

void RelayComponent::refresh()
{
    if (relay)
    {
        groupField.setText(relay->getGroup(), dontSendNotification);
    }
    else
    {
        groupField.setText("", dontSendNotification);
    }
    
    targetSelectionComponent.refresh();
}

void RelayComponent::labelTextChanged(Label *label)
{
    if (label == &groupField)
    {
        if (relay) relay->setGroup(groupField.getText());
    }
}

void RelayComponent::buttonClicked (Button* button)
{
    
}
