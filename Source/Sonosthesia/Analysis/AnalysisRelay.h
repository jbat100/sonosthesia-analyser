/*
  ==============================================================================

    AnalysisRelay.h
    Created: 8 Jul 2016 2:47:58pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSISRELAY_H_INCLUDED
#define ANALYSISRELAY_H_INCLUDED

#include "../../Audio Analysis/AudioAnalysisManager.h"
#include "../Core/Utils.h"
#include "../Relay/Relay.h"

class AnalysisRelay;

class AnalysisRelayListener {
public:
    virtual ~AnalysisRelayListener() {}
    virtual void analysisRelayChanged(AnalysisRelay* relay) = 0;
    virtual void analysisRelayInvalidated(AnalysisRelay* relay) = 0;
};

class AnalysisRelay : public Relay, public ListenerList<AnalysisRelayListener> {

public:
    
    AnalysisRelay();
    AnalysisRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, String _anaysisIdentifier);
    
    void setDescriptor(String _descriptor);
    String getDescriptor();
    
    void setAnaysisIdentifier(String _anaysisIdentifier);
    String getAnaysisIdentifier();
    
    // overrides to send change notifications
    void setTarget(std::shared_ptr<OSCTarget> _target);
    void setGroup(String _group);
    
    static const String noIdentifier;
    
private:
    
    String descriptor;
    String anaysisIdentifier;
    
};

class AnalysisRelayManager : public ListManager<AnalysisRelay> {
    
public:
    
    AnalysisRelayManager(AudioAnalysisManager& _analysisManager);
    
    void sendResults(); // push the results of all the analyses according to the relays
    
    bool analysisIsRelayed(String analysisIdentifier);
    
private:
    
    AudioAnalysisManager& analysisManager;
    
};


#endif  // ANALYSISRELAY_H_INCLUDED
