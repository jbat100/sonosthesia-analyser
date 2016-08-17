/*
  ==============================================================================

    ListControllerComponent.cpp
    Created: 2 Jul 2016 1:19:18pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ListControllerComponent.h"
#include "Theme.h"

//==============================================================================
ListControllerComponent::ListControllerComponent(const String& description)
{
    setOpaque(false);
    
    addAndMakeVisible(descriptionLabel);
    descriptionLabel.setText(description, dontSendNotification);
    Appearence::theme()->label(descriptionLabel);
    descriptionLabel.setJustificationType(Justification::left);
    
    addAndMakeVisible(newButton);
    newButton.addListener(this);
    newButton.setButtonText("New");
    
    addAndMakeVisible(clearButton);
    clearButton.addListener(this);
    clearButton.setButtonText("Clear");
    
}

ListControllerComponent::~ListControllerComponent()
{
}

void ListControllerComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black.withAlpha(0.3f));
}

void ListControllerComponent::resized()
{
    int labelHeight = 25;
    int buttonHeight = 20;
    int buttonWidth = 60;
    int hmargin = 10;
    int vmargin = 4;
    int spacing = 10;
    
    Rectangle<int> bounds = getBounds();
    int hackyAdjust = 0;
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin - hackyAdjust, vmargin);
    int horizontalOffset = hmargin;
    
    int labelWidth = rootBounds.getWidth() - (2* buttonWidth) - (2*spacing);
    Rectangle<int> labelBounds (horizontalOffset, vmargin, labelWidth, labelHeight);
    descriptionLabel.setBounds(labelBounds);
    horizontalOffset = descriptionLabel.getRight() + spacing;
    
    int vAdjust = 5;
    newButton.setBounds( Rectangle<int>(horizontalOffset, vmargin + vAdjust, buttonWidth, buttonHeight) );
    horizontalOffset = newButton.getRight() + spacing;
    clearButton.setBounds( Rectangle<int>(horizontalOffset, vmargin + vAdjust, buttonWidth, buttonHeight) );
    
}

void ListControllerComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        call(&ListControllerListener::newItemRequest, this);
    }
    else if (button == &clearButton)
    {
        call(&ListControllerListener::clearItemsRequest, this);
    }
}

