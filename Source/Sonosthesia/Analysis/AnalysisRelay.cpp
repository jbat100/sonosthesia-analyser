/*
  ==============================================================================

    AnalysisRelay.cpp
    Created: 8 Jul 2016 2:47:58pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "AnalysisRelay.h"

#include "AnalysisRelay.h"

AnalysisRelay::AnalysisRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, String _anaysisIdentifier)
{
    
}

void AnalysisRelay::setDescriptor(String _descriptor)
{
    descriptor = _descriptor;
}

String AnalysisRelay::getDescriptor()
{
    return descriptor;
}

void AnalysisRelay::setAnaysisIdentifier(String _anaysisIdentifier)
{
    anaysisIdentifier = _anaysisIdentifier;
}

String AnalysisRelay::getAnaysisIdentifier()
{
    return anaysisIdentifier;
}

void AnalysisRelayManager::sendResults()
{
    
}