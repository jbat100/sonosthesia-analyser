/*
  ==============================================================================

    OSCTargetManager.h
    Created: 12 May 2016 4:47:23pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef OSCTARGETMANAGER_H_INCLUDED
#define OSCTARGETMANAGER_H_INCLUDED

#include "Utils.h"

#include "../JuceLibraryCode/JuceHeader.h"

#include <vector>
#include <memory>


class OSCTarget;

class OSCTargetListener
{
public:
    
    virtual ~OSCTargetListener()  {}
    
    virtual void targetInvalidated(OSCTarget* target) {};
    
    virtual void targetChanged(OSCTarget* target) {};
};

class OSCTarget : public ListenerList<OSCTargetListener>
{
public:
    
    OSCTarget();
    OSCTarget(String _hostName, int _portNumber);
    
    // should only use this for xml loading, otherwise should let the identifier be created internally
    // should really be private with a friend writer class, but I'm lazy...
    OSCTarget(String _identifier, String _hostName, int _portNumber);
    
    void setHostName(String _hostName);
    String getHostName();
    
    void setPortNumber(int _portNumber);
    int getPortNumber();
    
    // target can never be used again, doing so will cause an exception
    void invalidate();
    void checkValidity();
    
    bool reconnect();
    bool isConnected();
    
    String getIdentifier();
    
    void sendMessage(const OSCMessage& message);
    void sendBundle(const OSCBundle& message);
    void enqueueMessage(const OSCMessage& message);
    void purgeMessages();
    
private:
    
    String hostName;
    int portNumber;
    OSCSender sender;
    bool connected;
    bool valid;
    String identifier;
    
    void updateSender();
};


class OSCTargetManager : public ListManager<OSCTarget>
{
public:
    void invalidateAll();
};


#endif  // OSCTARGETMANAGER_H_INCLUDED
