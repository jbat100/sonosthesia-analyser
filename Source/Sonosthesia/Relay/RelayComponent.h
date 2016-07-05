/*
  ==============================================================================

    RelayComponent.h
    Created: 16 May 2016 4:07:30pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef RELAYCOMPONENT_H_INCLUDED
#define RELAYCOMPONENT_H_INCLUDED

#include "Utils.h"
#include "Relay.h"
#include "TargetManager.h"


//==============================================================================
// This is a custom component containing used for selecting a midi channel

class TargetSelectionComponent : public Component, private ComboBoxListener, private ChangeListener, OSCTargetListener
{
public:
    TargetSelectionComponent (OSCTargetManager& _manager);
    
    void refresh();
    
    void setRelay (std::shared_ptr<Relay> _relay);
    
    // ======== Component =======
    
    virtual void resized() override;
    
    // ==== ComboBoxListener ====
    
    virtual void comboBoxChanged (ComboBox*) override;
    
    // ==== ChangeListener ====
    
    virtual void changeListenerCallback (ChangeBroadcaster* source) override;
    
    // === OSCTargetListener ==
    
    virtual void targetInvalidated(OSCTarget* target) override;
    
    virtual void targetChanged(OSCTarget* target) override;
    
private:
    
    void updateComboBox();
    
    void listenToAllTargets();
    
    ComboBox comboBox;
    std::shared_ptr<Relay> relay;
    OSCTargetManager& manager;
    NumericIdentifierGenerator generator;
    
    static const int noSelection;
    static const String noSelectionText;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetSelectionComponent)
};




//==============================================================================
/*  A component associated with a target
 */

class RelayComponent : public Component, protected LabelListener, protected ButtonListener  {
    
public:
    
    RelayComponent(OSCTargetManager& _targetManager);
    
    virtual void setRelay(std::shared_ptr<Relay> _relay);
    
    std::shared_ptr<Relay> getRelay();
    
    virtual void refresh();
    
    // ======== LabelListener ==========
    
    virtual void labelTextChanged(Label *label) override;
    
    // ======== ButtonListener =========
    
    virtual void buttonClicked (Button* button) override;
    
protected:
    
    OSCTargetManager& targetManager;
    std::shared_ptr<Relay> relay;
    
    Label groupLabel;
    Label groupField;
    
    Label targetLabel;
    TargetSelectionComponent targetSelectionComponent;
    
    TextButton deleteButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RelayComponent)
    
};





#endif  // RELAYCOMPONENT_H_INCLUDED
