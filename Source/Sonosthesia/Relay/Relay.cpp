/*
  ==============================================================================

    Relay.cpp
    Created: 16 May 2016 4:07:07pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "Relay.h"


Relay::Relay() :
    group("default"),
    identifier(Uuid().toString())
{
    setTarget(nullptr);
}

Relay::Relay(std::shared_ptr<OSCTarget> _target, String _group) :
    group(_group),
    identifier(Uuid().toString())
{
    setTarget(_target);
}

Relay::Relay(String _identifier, std::shared_ptr<OSCTarget> _target, String _group) :
    group(_group),
    identifier(_identifier)
{
    setTarget(_target);
}

Relay::~Relay()
{
    if (target)
    {
        std::cout << "Relay removing target listener on destruction\n";
        target->remove(this);
    }
}


std::shared_ptr<OSCTarget> Relay::getTarget()
{
    return target;
}

void Relay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    if (_target == target) return;
    
    // if we already have a target then stop listening to notifications
    if (target)
    {
        target->remove(this);
    }
    
    if (_target)
    {
        std::cout << "Relay setTarget : " << _target->getHostName() << ":" << _target->getPortNumber() << "\n";
        _target->checkValidity();
        _target->add(this);
    }
    
    target = _target;
}

void Relay::setGroup(String _group)
{
    group = _group;
}

String Relay::getGroup()
{
    return group;
}

String Relay::getIdentifier()
{
    return identifier;
}

void Relay::targetInvalidated (OSCTarget* _target)
{
    if (_target != target.get())
    {
        throw std::runtime_error("unexpected target invalidation callback");
    }
    
    std::cout << "Relay nulling target on invalidation\n";
    
    target = nullptr;
}


