/*
  ==============================================================================

    AnalysisBuffer.h
    Created: 5 Jul 2016 10:29:45pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSISBUFFER_H_INCLUDED
#define ANALYSISBUFFER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//=======================================================================
/** A class to manage an audio buffer, which may be different to the host
 * audio frame size. It will fill with audio samples and then indicate it
 * is ready to be processed. This allows a consistent audio analysis buffer
 * size, even if the host frame size changes
 */
class AnalysisBuffer {
    
public:
    /** Constructor */
    AnalysisBuffer (int bufferSize_);
    
    /** Adds a number of new audio samples to the audio buffer
     * @param samples a pointer to an array containing the samples to add to the buffer
     * @param numSamples the number of samples in the array
     */
    void addNewSamplesToBuffer (float*samples, int numSamples);
    
    /** Sets the buffer size
     * @param bufferSize_ the new buffer size
     */
    void setBufferSize (int bufferSize_);
    
    /** @returns the buffer size */
    int getBufferSize();
    
    /** A vector to hold the audio buffer samples */
    std::vector<float> buffer;
    
    /** @returns true if the buffer is now full and ready for processing */
    bool isReady();
    
private:
    
    /** The buffer size */
    int bufferSize;
    
    /** A boolean indicating whether or not the buffer is full and ready for processing */
    bool bufferReady;
    
    /** Keeps a count of the number of samples collected */
    int numSamplesCollected;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalysisBuffer)
};


#endif  // ANALYSISBUFFER_H_INCLUDED
