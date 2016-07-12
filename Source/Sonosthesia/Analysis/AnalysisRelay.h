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

class AnalysisRelay : public Relay {

public:
    
    AnalysisRelay();
    AnalysisRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, String _anaysisIdentifier);
    
    void setDescriptor(String _descriptor);
    String getDescriptor();
    
    void setAnaysisIdentifier(String _anaysisIdentifier);
    String getAnaysisIdentifier();
    
    static const String noIdentifier;
    
private:
    
    String descriptor;
    String anaysisIdentifier;
    
};

class AnalysisRelayManager : public ListManager<AnalysisRelay> {
    
public:
    
    AnalysisRelayManager(AudioAnalysisManager& _analysisManager);
    
    void sendResults(); // push the results of all the analyses according to the relays
    
private:
    
    AudioAnalysisManager& analysisManager;
    
};


#endif  // ANALYSISRELAY_H_INCLUDED
