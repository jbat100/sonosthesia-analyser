/*
  ==============================================================================

    AnalysisRelay.cpp
    Created: 8 Jul 2016 2:47:58pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "AnalysisRelay.h"

#include "AnalysisRelay.h"

const String AnalysisRelay::noIdentifier = "None";

AnalysisRelay::AnalysisRelay() :
    Relay(),
    descriptor("default"),
    anaysisIdentifier(noIdentifier)
{
    
}

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

AnalysisRelayManager::AnalysisRelayManager(AudioAnalysisManager& _analysisManager) : analysisManager(_analysisManager)
{
    
}

void AnalysisRelayManager::sendResults()
{
    auto items = getItems();
    
    for (auto i = items.begin(); i != items.end(); ++i)
    {
        std::shared_ptr<AnalysisRelay> relay = *i;
        std::shared_ptr<OSCTarget> target = relay->getTarget();
        String identifier = relay->getAnaysisIdentifier();
        if (identifier == AnalysisRelay::noIdentifier)
        {
            continue;
        }
        AudioAnalysis* analysis = analysisManager.getAnalysisWithIdentifier(identifier);
        if (analysis && target && analysis->resultReady())
        {
            OSCAddressPattern pattern = OSCAddressPattern("/" + relay->getGroup() + "/" + relay->getDescriptor() + "/");
            OSCMessage message = OSCMessage(pattern);
            
            if (analysis->getOutputType() == FloatOutput)
            {
                float output = analysis->getAnalysisResultAsFloat();
                message.addFloat32(output);
            }
            else if (analysis->getOutputType() == VectorOutput)
            {
                std::vector<float> output = analysis->getAnalysisResultAsVector();
                for (int i = 0;i < output.size();i++)
                {
                    message.addFloat32(output[i]);
                }
            }
            target->sendMessage(message);
        }
    }
}
