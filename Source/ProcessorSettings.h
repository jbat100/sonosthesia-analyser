/*
  ==============================================================================

    ProcessorSettings.h
    Created: 28 Jul 2016 10:23:16pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PROCESSORSETTINGS_H_INCLUDED
#define PROCESSORSETTINGS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "ProcessorModel.h"

#define DEFAULT_BUFFER_SIZE 1024
#define DEFAULT_SAMPLING_FREQUENCY 44100

// Settings should be accessible globaly without needing to go through the actual processor

enum BufferSizeValues
{
    BufferSize64,
    BufferSize128,
    BufferSize256,
    BufferSize512,
    BufferSize1024,
    BufferSize2048,
    BufferSize4096,
    NumBufferSizes
};

class ProcessorSettings;

class ProcessorSettingsListnener {
    
public:
    virtual ~ProcessorSettingsListnener() {}
    virtual void processorBufferSizeChanged(ProcessorSettings* settings) {}
    virtual void processorHostFrameSizeChanged(ProcessorSettings* settings) {}
    virtual void processorSamplingFrequencyChanged(ProcessorSettings* settings) {}
    
};

class ProcessorSettings : public ListenerList<ProcessorSettingsListnener> {
    
private:
    
    int bufferSize;
    int hostFrameSize;
    int samplingFrequency;
    
public:
    
    ProcessorSettings();
    
    static ProcessorSettings* getInstance()
    {
        // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
        
        static ProcessorSettings instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return &instance;
    }
    
    virtual ~ProcessorSettings()
    {
        //clearSingletonInstance();
    }
    
    /** Save state to a value tree */
    virtual ValueTree saveToValueTree()
    {
        ValueTree tree;
        tree.setProperty(AnalyserProperties::BufferSize, bufferSize, nullptr);
        return tree;
    }
    
    /** Load state from a value tree */
    virtual void loadFromValueTree(ValueTree &tree)
    {
        setBufferSize( tree[AnalyserProperties::BufferSize] );
    }
    
    int getBufferSize()
    {
        return bufferSize;
    }
    
    void setBufferSize(int _bufferSize)
    {
        bufferSize = _bufferSize;
        call(&ProcessorSettingsListnener::processorBufferSizeChanged, this);
    }
    
    int getSamplingFrequency()
    {
        return samplingFrequency;
    }
    
    void setSamplingFrequency(int _samplingFrequency)
    {
        samplingFrequency = _samplingFrequency;
        call(&ProcessorSettingsListnener::processorSamplingFrequencyChanged, this);
    }
    
    int getHostFrameSize()
    {
        return hostFrameSize;
    }
    
    void setHostFrameSize(int _hostFrameSize)
    {
        hostFrameSize = _hostFrameSize; // does anyone need to be informed of this change?
        call(&ProcessorSettingsListnener::processorHostFrameSizeChanged, this);
    }
    
    //juce_DeclareSingleton(ProcessorSettings, false);
};

//juce_ImplementSingleton(ProcessorSettings);


#endif  // PROCESSORSETTINGS_H_INCLUDED
