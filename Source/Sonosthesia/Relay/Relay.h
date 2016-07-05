/*
  ==============================================================================

    Relay.h
    Created: 16 May 2016 4:07:07pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef RELAY_H_INCLUDED
#define RELAY_H_INCLUDED

#include <list>
#include <memory>

#include "../Target/TargetManager.h"

class Relay : public OSCTargetListener
{
public:
    
    Relay();
    Relay(std::shared_ptr<OSCTarget> _target, String _group);
    
    Relay(String _identifier, std::shared_ptr<OSCTarget> _target, String _group);
    
    virtual ~Relay();
    
    std::shared_ptr<OSCTarget> getTarget();
    virtual void setTarget(std::shared_ptr<OSCTarget> _target);
    
    String getGroup();
    virtual void setGroup(String _group);
    
    String getIdentifier();
    
    // change listener, in case the osc target is invalidated
    
    void targetInvalidated (OSCTarget* _target) override;
    
private:
    
    String group;
    std::shared_ptr<OSCTarget> target;
    String identifier;
};




#endif  // RELAY_H_INCLUDED
