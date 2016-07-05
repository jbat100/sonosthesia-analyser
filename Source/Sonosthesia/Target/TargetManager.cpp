/*
  ==============================================================================

    OSCTargetManager.cpp
    Created: 12 May 2016 4:47:23pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "TargetManager.h"

OSCTarget::OSCTarget() :
    hostName("127.0.0.1"),
    portNumber(3333),
    connected(false),
    valid(true),
    identifier(Uuid().toString())
{
    updateSender();
}

OSCTarget::OSCTarget(String _hostName, int _portNumber) :
    hostName(_hostName),
    portNumber(_portNumber),
    connected(false),
    valid(true),
    identifier(Uuid().toString())
{
    updateSender();
}

OSCTarget::OSCTarget(String _identifier, String _hostName, int _portNumber) :
    hostName(_hostName),
    portNumber(_portNumber),
    connected(false),
    valid(true),
    identifier(_identifier)
{
    updateSender();
}

void OSCTarget::invalidate()
{
    std::cout << "OSCTarget invalidated\n";
    checkValidity();
    sender.disconnect();
    valid = false;
    call(&OSCTargetListener::targetInvalidated, this);
    clear();
}

bool OSCTarget::reconnect()
{
    checkValidity();
    updateSender();
    return connected;
}

bool OSCTarget::isConnected()
{
    checkValidity();
    return connected;
}
    
void OSCTarget::setHostName(String _hostName)
{
    checkValidity();
    hostName = _hostName;
    updateSender();
    call(&OSCTargetListener::targetChanged, this);
}

String OSCTarget::getHostName()
{
    return hostName;
}
    
void OSCTarget::setPortNumber(int _portNumber)
{
    checkValidity();
    portNumber = _portNumber;
    updateSender();
    call(&OSCTargetListener::targetChanged, this);
}

int OSCTarget::getPortNumber()
{
    return portNumber;
}
    
String OSCTarget::getIdentifier()
{
    return identifier;
}

void OSCTarget::sendMessage(const OSCMessage& message)
{
    checkValidity();
    sender.send(message);
}

void OSCTarget::sendBundle(const OSCBundle& bundle)
{
    checkValidity();
    sender.send(bundle);
}

void OSCTarget::enqueueMessage(const OSCMessage& message)
{
    throw std::runtime_error("unimplemented");
}

void OSCTarget::purgeMessages()
{
    throw std::runtime_error("unimplemented");
}


void OSCTarget::updateSender()
{
    checkValidity();
    sender.disconnect();
    connected = sender.connect(hostName, portNumber);
    std::cout << "Connecting " << hostName << ":" << portNumber;
    if (connected) std::cout << " (success)\n";
    else std::cout << " (failure)\n";
}

void OSCTarget::checkValidity()
{
    if (!valid) throw std::runtime_error("used invalidated target");
}

void OSCTargetManager::invalidateAll()
{
    auto items = getItems();
    
    for (auto i = items.begin(); i != items.end(); i++)
    {
        (*i)->invalidate();
    }
}
