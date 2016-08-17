/*
  ==============================================================================

    ListControllerComponent.h
    Created: 2 Jul 2016 1:19:18pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef LISTCONTROLLERCOMPONENT_H_INCLUDED
#define LISTCONTROLLERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class ListControllerListener
{
public:
    
    virtual ~ListControllerListener()  {}
    
    virtual void newItemRequest(Component* sender) = 0;
    
    virtual void clearItemsRequest(Component* sender) = 0;
};

//==============================================================================
/*
*/
class ListControllerComponent : public Component, public ButtonListener, public ListenerList<ListControllerListener>
{
public:
    ListControllerComponent(const String& description);
    ~ListControllerComponent();

    // ======== Component =========
    
    virtual void paint (Graphics&) override;
    virtual void resized() override;
    
    // ======== Button::Listener =========
    
    virtual void buttonClicked (Button* button) override;

private:
    
    Label descriptionLabel;
    
    TextButton newButton;
    TextButton clearButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListControllerComponent)
};


#endif  // LISTCONTROLLERCOMPONENT_H_INCLUDED
