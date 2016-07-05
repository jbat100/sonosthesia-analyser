/*
  ==============================================================================

    AnalysisBuffer.cpp
    Created: 5 Jul 2016 10:29:45pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "AnalysisBuffer.h"

//==============================================================================
AnalysisBuffer::AnalysisBuffer (int bufferSize_) : bufferReady(false), numSamplesCollected(0)
{
    
}

//==============================================================================
void AnalysisBuffer::setBufferSize (int bufferSize_)
{
    // initialise buffer length
    bufferSize = bufferSize_;
    
    // resize the buffer vector to hold the right number of samples
    buffer.resize(bufferSize);
    
    // initialise the buffer to zeros
    for (int i = 0;i < bufferSize;i++)
    {
        buffer[i] = 0.0;
    }
}

//==============================================================================
void AnalysisBuffer::addNewSamplesToBuffer (float* samples,int numSamples)
{
    bufferReady = false;
    
    // if the number of new samples does not
    // exceed the buffer length
    if (numSamples <= bufferSize)
    {
        // shift back existing audio samples
        for (int k = 0;k < (bufferSize - numSamples);k++)
        {
            buffer[k] = buffer[k+numSamples];
        }
        
        // now copy the new samples to the remaining part of the buffer
        int j = 0;
        for (int k = bufferSize-numSamples;k < bufferSize;k++)
        {
            buffer[k] = samples[j];
            j++;
        }
        
        numSamplesCollected += numSamples;
        
        if (numSamplesCollected >= bufferSize)
        {
            bufferReady = true;
            numSamplesCollected = 0;
        }
    }
    else // otherwise we have more samples than our buffer can hold
    {
        // in this case, we will copy the most recent samples to the buffer
        for (int k = 0;k < bufferSize;k++)
        {
            buffer[k] = samples[numSamples-bufferSize+k];
        }
        
        bufferReady = true;
    }
}

//==============================================================================
int AnalysisBuffer::getBufferSize()
{
    return bufferSize;
}

//==============================================================================
bool AnalysisBuffer::isReady()
{
    return bufferReady;
}
