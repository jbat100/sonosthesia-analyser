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

class ProcessorSettings {
    
private:
    
    int bufferSize;
    
public:
    
    ProcessorSettings() {}
    
    ~ProcessorSettings()
    {
        clearSingletonInstance();
    }
    
    int getBufferSize()
    {
        return bufferSize;
    }
    
    void setBufferSize(int _bufferSize)
    {
        bufferSize = _bufferSize;
    }
    
    juce_DeclareSingleton(ProcessorSettings, false);
};

juce_ImplementSingleton(ProcessorSettings);


#endif  // PROCESSORSETTINGS_H_INCLUDED
