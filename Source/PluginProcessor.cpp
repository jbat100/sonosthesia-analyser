//=======================================================================
/** @file PluginProcessor.cpp
 *  @brief The top level audio processing class for the Sound Analyser
 *  @author Adam Stark
 *  @copyright Copyright (C) 2014  Adam Stark
 *
 * This file is part of Sound Analyser.
 *
 * Sound Analyser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sound Analyser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sound Analyser.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ProcessorSettings.h"



//==============================================================================
SoundAnalyserAudioProcessor::SoundAnalyserAudioProcessor() :
    analyser(),
    analysisRelayManager(analyser)
{    

}

//==============================================================================
SoundAnalyserAudioProcessor::~SoundAnalyserAudioProcessor()
{
    
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

//==============================================================================
int SoundAnalyserAudioProcessor::getNumParameters()
{
    return 0;
}

//==============================================================================
float SoundAnalyserAudioProcessor::getParameter (int index)
{
    switch (index)
    {
        default:
            return 0.0f;
    }
}

//==============================================================================
void SoundAnalyserAudioProcessor::setParameter (int index, float newValue)
{
    switch (index)
    {
        default:
            break;
    }
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        default:
            break;
    }
    
    return String::empty;
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

//==============================================================================
bool SoundAnalyserAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

//==============================================================================
bool SoundAnalyserAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

//==============================================================================
bool SoundAnalyserAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
bool SoundAnalyserAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

//==============================================================================
bool SoundAnalyserAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

//==============================================================================
double SoundAnalyserAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
int SoundAnalyserAudioProcessor::getNumPrograms()
{
    return 1;
}

//==============================================================================
int SoundAnalyserAudioProcessor::getCurrentProgram()
{
    return 0;
}

//==============================================================================
void SoundAnalyserAudioProcessor::setCurrentProgram (int index)
{
}

//==============================================================================
const String SoundAnalyserAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

//==============================================================================
void SoundAnalyserAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SoundAnalyserAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    ProcessorSettings::getInstance()->setHostFrameSize(samplesPerBlock);
    ProcessorSettings::getInstance()->setSamplingFrequency((int)sampleRate);
    
    //analyser.setSamplingFrequency((int)sampleRate);
    //analyser.setHostFrameSize(samplesPerBlock);
}

//==============================================================================
void SoundAnalyserAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

//==============================================================================
void SoundAnalyserAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        if (channel == 0)
        {
            analyser.analyseAudio(channelData, buffer.getNumSamples());
            analysisRelayManager.sendResults();
        }
    }
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool SoundAnalyserAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

//==============================================================================
AudioProcessorEditor* SoundAnalyserAudioProcessor::createEditor()
{
    std::cout << "Create editor\n";
    return new SoundAnalyserAudioProcessorEditor (this);
}

//==============================================================================
void SoundAnalyserAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    std::cout << "Saving state\n";
    
    ValueTree tree = ValueTree(Identifier("analyser"));
    
    // store all state to tree
    
    tree.setProperty(AnalyserProperties::BufferSize, ProcessorSettings::getInstance()->getBufferSize(), nullptr);
    
    for (int i = 0;i < analyser.audioAnalyses.size(); i++)
    {
        ValueTree analysisTree = analyser.audioAnalyses[i]->saveToValueTree();
        tree.addChild(analysisTree, 0, nullptr);
    }
    
    ScopedPointer<XmlElement> xml = tree.createXml();
    
    // Store targets...
    XmlElement* targetsElement = xml->createNewChildElement("targets");
    auto targets = targetManager.getItems();
    for (auto i = targets.begin(); i != targets.end(); i++)
    {
        XmlElement* targetElement = targetsElement->createNewChildElement("target");
        saveOSCTarget((*i), targetElement);
    }
    
    // Store relays...
    XmlElement* relaysElement = xml->createNewChildElement("relays");
    auto relays = analysisRelayManager.getItems();
    for (auto i = relays.begin(); i != relays.end(); i++)
    {
        XmlElement* relayElement = relaysElement->createNewChildElement("relay");
        saveAnalysisRelay((*i), relayElement);
    }
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (*xml, destData);
}

//==============================================================================
void SoundAnalyserAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::cout << "Restoring state\n";
    
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    ValueTree tree = ValueTree::fromXml(*xmlState);
    
    std::cout << "SoundAnalyserAudioProcessor setStateInformation tree is " << (tree.isValid() ? "valid" : "invalid") << "\n";
    
    // update all state from
    
    if (tree.hasProperty(AnalyserProperties::BufferSize))
    {
        ProcessorSettings::getInstance()->setBufferSize(tree[AnalyserProperties::BufferSize]);
    }
    
    for (int i = 0;i < analyser.audioAnalyses.size();i++)
    {
        Identifier identifier = analyser.audioAnalyses[i]->getIdentifier();
        ValueTree analysisTree = tree.getChildWithName(identifier);
        if (analysisTree.isValid())
        {
            analyser.audioAnalyses[i]->loadFromValueTree(analysisTree);
        }
        else
        {
            //std::cerr << "SoundAnalyserAudioProcessor setStateInformation invalid analysis tree\n";
        }
    }
    
    
    
    // order is important, targets must be loaded first, as the relays will need them
    XmlElement* targetsElement = xmlState->getChildByName("targets");
    if (targetsElement)
    {
        for (int i = 0; i < targetsElement->getNumChildElements(); i++)
        {
            XmlElement* targetElement = targetsElement->getChildElement(i);
            auto target = loadOSCTarget(targetElement);
            targetManager.addItem(target);
        }
    }
    
    // load midi relays
    XmlElement* relaysElement = xmlState->getChildByName("relays");
    if (relaysElement)
    {
        for (int i = 0; i < relaysElement->getNumChildElements(); i++)
        {
            XmlElement* relayElement = relaysElement->getChildElement(i);
            auto midiRelay = loadAnalysisRelay(relayElement);
            analysisRelayManager.addItem(midiRelay);
        }
    }
    
}


//==============================================================================

void SoundAnalyserAudioProcessor::saveOSCTarget(std::shared_ptr<OSCTarget> target, XmlElement* element)
{
    element->setAttribute("identifier", target->getIdentifier());
    element->setAttribute("hostname", target->getHostName());
    element->setAttribute("portnumber", target->getPortNumber());
}

std::shared_ptr<OSCTarget> SoundAnalyserAudioProcessor::loadOSCTarget(XmlElement* element)
{
    String identifier = element->getStringAttribute("identifier");
    String hostName = element->getStringAttribute("hostname");
    int portNumber = element->getIntAttribute("portnumber");
    return std::shared_ptr<OSCTarget> (new OSCTarget(identifier, hostName, portNumber));
}

void SoundAnalyserAudioProcessor::saveAnalysisRelay(std::shared_ptr<AnalysisRelay> relay, XmlElement* element)
{
    element->setAttribute("identifier", relay->getIdentifier());
    element->setAttribute("analysis", relay->getAnaysisIdentifier());
    element->setAttribute("group", relay->getGroup());
    element->setAttribute("descriptor", relay->getDescriptor());
    if (relay->getTarget()) element->setAttribute("target", relay->getTarget()->getIdentifier());
}

std::shared_ptr<AnalysisRelay> SoundAnalyserAudioProcessor::loadAnalysisRelay(XmlElement* element)
{
    String identifier = element->getStringAttribute("identifier");
    String group = element->getStringAttribute("group");
    String descriptor = element->getStringAttribute("descriptor");
    String analysis = element->getStringAttribute("analysis");
    std::shared_ptr<OSCTarget> target = getTargetForElement(element);
    return std::shared_ptr<AnalysisRelay> (new AnalysisRelay(identifier, target, group, descriptor, analysis));
}

std::shared_ptr<OSCTarget> SoundAnalyserAudioProcessor::getTargetForElement(XmlElement* element)
{
    std::shared_ptr<OSCTarget> target = nullptr;
    if (element->hasAttribute("target"))
    {
        try
        {
            target = targetManager.getItem(element->getStringAttribute("target"));
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Invalid target identifier" << "\n";
        }
    }
    return target;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SoundAnalyserAudioProcessor();
}

OSCTargetManager& SoundAnalyserAudioProcessor::getTargetManager()
{
    return targetManager;
}

AnalysisRelayManager& SoundAnalyserAudioProcessor::getAnalysisRelayManager()
{
    return analysisRelayManager;
}

