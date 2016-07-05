/*
  ==============================================================================

    TargetListComponent.cpp
    Created: 26 May 2016 3:00:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TargetListComponent.h"
#include "Theme.h"

const int TargetComponent::desiredHeight = 40;
const int TargetComponent::hmargin = 10;
const int TargetComponent::buttonHeight = 20;

TargetComponent::TargetComponent(OSCTargetManager& _manager) : manager(_manager), target(nullptr)
{
    setOpaque(false);
    
    addAndMakeVisible(hostLabel);
    hostLabel.setText("Host", dontSendNotification);
    Appearence::theme()->label(hostLabel);
    
    addAndMakeVisible(hostField);
    hostField.setEditable(false, true, false);
    hostField.addListener(this);
    Appearence::theme()->field(hostField);
    
    addAndMakeVisible(portLabel);
    portLabel.setText("Port", dontSendNotification);
    Appearence::theme()->label(portLabel);
    
    addAndMakeVisible(portField);
    portField.setEditable(false, true, false);
    portField.addListener(this);
    Appearence::theme()->field(portField);
    
    addAndMakeVisible(statusLabel);
    Appearence::theme()->indicator(statusLabel, Theme::Level::Warning);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setButtonText("Delete");
    Appearence::theme()->textButton(deleteButton);
    
}

void TargetComponent::setTarget(std::shared_ptr<OSCTarget> _target)
{
    if (target)
    {
        target->remove(this);
    }
    
    target = _target;
    
    if (target)
    {
        target->add(this);
    }
    
    refresh();
}

void TargetComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    
    b.setX(hmargin);
    b.setWidth( b.getWidth() - (hmargin*2) );
    b.setHeight( b.getHeight() - 10);
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(b, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(b.reduced(1), 5);
    
}

void TargetComponent::resized()
{
    int vmargin = 3;
    int hmargin = 20;
    int spacing = 10;
    
    int hostLabelWidth = 40;
    //int hostFieldWidth = 200; // hostname field will resize proportionally
    int portLabelWidth = 40;
    int portFieldWidth = 50;
    
    int statusLabelWidth = 100;
    
    int labelHeight = 20;
    int buttonWidth = 60;
    
    Rectangle<int> bounds = getBounds();
    
    int hackyAdjust = 20;
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin - hackyAdjust, vmargin);
    
    int fullWidth = rootBounds.getWidth();
    //int fullHeight = rootBounds.getHeight();
    int horizontalOffset = rootBounds.getX();
    
    Rectangle<int> hostLabelBounds = rootBounds.withX(horizontalOffset).withWidth(hostLabelWidth).withHeight(labelHeight);
    horizontalOffset = hostLabelBounds.getRight() + spacing;
    hostLabel.setBounds(hostLabelBounds);

    int hostFieldWidth = fullWidth - hostLabelWidth - portLabelWidth - portFieldWidth - buttonWidth - statusLabelWidth - (spacing*5);
    Rectangle<int> hostFieldBounds = rootBounds.withX(horizontalOffset).withWidth(hostFieldWidth).withHeight(labelHeight);
    horizontalOffset = hostFieldBounds.getRight() + spacing;
    hostField.setBounds(hostFieldBounds);
    
    Rectangle<int> portLabelBounds = rootBounds.withX(horizontalOffset).withWidth(portLabelWidth).withHeight(labelHeight);
    horizontalOffset = portLabelBounds.getRight() + spacing;
    portLabel.setBounds(portLabelBounds);
    
    Rectangle<int> portFieldBounds = rootBounds.withX(horizontalOffset).withWidth(portFieldWidth).withHeight(labelHeight);
    horizontalOffset = portFieldBounds.getRight() + spacing;
    portField.setBounds(portFieldBounds);
    
    Rectangle<int> statusLabelBounds = rootBounds.withX(horizontalOffset).withWidth(statusLabelWidth).withHeight(labelHeight);
    horizontalOffset = statusLabelBounds.getRight() + spacing;
    statusLabel.setBounds(statusLabelBounds);
    
    Rectangle<int> deleteButtonBounds = rootBounds.withX(horizontalOffset).withWidth(buttonWidth).withHeight(buttonHeight);
    horizontalOffset = deleteButtonBounds.getRight() + spacing;
    deleteButton.setBounds(deleteButtonBounds);
    
}

void TargetComponent::buttonClicked (Button* button)
{
    if (button == &deleteButton)
    {
        if (target) manager.deleteItem(target->getIdentifier());
    }
}

void TargetComponent::labelTextChanged(Label *label)
{
    if (!target) return;
    
    if (label == &hostField)
    {
         target->setHostName(label->getText());
    }
    else if (label == &portField)
    {
        int port = label->getText().getIntValue();
        
        if (port > 0)
        {
            target->setPortNumber(port);
        }
        else
        {
            refresh(); // sets the field back to its current valid value
        }
    }
    
}

void TargetComponent::targetInvalidated(OSCTarget* _target)
{
    if (target.get() == _target)
    {
        setTarget(nullptr);
    }
}

void TargetComponent::refresh()
{
    if (target)
    {
        hostField.setText(target->getHostName(), dontSendNotification);
        portField.setText(String(target->getPortNumber()), dontSendNotification);
        statusLabel.setText(target->isConnected() ? "Connected" : "Disconnected", dontSendNotification);
        Appearence::theme()->indicator(statusLabel, target->isConnected() ? Theme::Level::Primary : Theme::Level::Warning);
    }
    else
    {
        hostField.setText("", dontSendNotification);
        portField.setText("", dontSendNotification);
        statusLabel.setText("", dontSendNotification);
    }
}

//==============================================================================
TargetListComponent::TargetListComponent(OSCTargetManager& _oscTargetManager) :
    listController("Create OSC targets"),
    oscTargetManager(_oscTargetManager)
{
    setOpaque(false);
    
    addAndMakeVisible(listController);
    listController.add(this);
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(TargetComponent::desiredHeight + 10);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
    
    oscTargetManager.addChangeListener(this);
}

TargetListComponent::~TargetListComponent()
{
}

void TargetListComponent::paint (Graphics& g)
{

}

void TargetListComponent::resized()
{
    int controllerHeight = 45;
    int hmargin = 4;
    int vmargin = 4;
    int vspacing = 4;
    
    Rectangle<int> rootBounds = getBounds();
    int verticalOffset = vmargin;
    int width = rootBounds.getWidth();
    
    int listHeight = rootBounds.getHeight() - controllerHeight;
    
    listBox.setBounds( Rectangle<int>(hmargin, vmargin, width, listHeight) );
    verticalOffset = listBox.getBottom() + vspacing;
    
    listController.setBounds( Rectangle<int>(0, verticalOffset, width, controllerHeight) );
}

void TargetListComponent::newItemRequest(Component* sender)
{
    oscTargetManager.newItem();
    listBox.updateContent();
}

void TargetListComponent::clearItemsRequest(Component* sender)
{
    oscTargetManager.invalidateAll();
    oscTargetManager.clear();
    listBox.updateContent();
}

int TargetListComponent::getNumRows()
{
    return oscTargetManager.count();
}

void TargetListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{

}

Component* TargetListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    TargetComponent* targetComponent = static_cast<TargetComponent*> (existingComponentToUpdate);
    
    std::shared_ptr<OSCTarget> target = nullptr;
    
    if (rowNumber < oscTargetManager.count())
    {
        target = oscTargetManager.getItem(rowNumber);
    }
    
    // If an existing component is being passed-in for updating, we'll re-use it, but
    // if not, we'll have to create one.
    if (targetComponent == nullptr)
    {
        targetComponent = new TargetComponent(oscTargetManager);
    }
    
    targetComponent->setTarget(target);
    return targetComponent;
}

void TargetListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&oscTargetManager))
    {
        listBox.updateContent();
    }
}
