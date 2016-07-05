/*
  ==============================================================================

    AnalysisManager.h
    Created: 5 Jul 2016 9:53:15pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSISMANAGER_H_INCLUDED
#define ANALYSISMANAGER_H_INCLUDED


//=======================================================================
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioAnalysisBuffer.h"
#include "Analysis.h"
#include "../../Libraries/Gist/src/Gist.h"

//=======================================================================
// import all audio analysis modules

#include "../../Modules/RMS.h"
#include "../../Modules/PeakEnergy.h"
#include "../../Modules/ZeroCrossingRate.h"
#include "../../Modules/SpectralCentroid.h"
#include "../../Modules/SpectralCrest.h"
#include "../../Modules/SpectralDifference.h"
#include "../../Modules/SpectralFlatness.h"
#include "../../Modules/FFTMagnitudeSpectrum.h"
#include "../../Modules/Pitch.h"
#include "../../Modules/MelFrequencySpectrum.h"
#include "../../Modules/SP_Chromagram.h"
#include "../../Modules/SP_ChordDetector.h"

#define DEFAULT_SAMPLING_FREQUENCY 44100

//=======================================================================
/** A class to manage audio input and all audio analysis modules
 */
class AnalysisManager {
    
public:
    
    /** Constructor */
    AnalysisManager(int bufferSize_);
    
    /** Passes the audio buffer through a number of analysis algorithms
     * @param buffer the audio buffer containing the audio samples
     * @param numSamples the number of audio samples in the buffer
     */
    void analyseAudio(float* buffer,int numSamples);
    
    /** Set the audio buffer size to be used for audio analysis. Note that this is
     * not (necessarily) the host audio frame size as the AudioAnalysisManager will
     * use an AudioBuffer object to manage audio buffer sizes
     * @param bufferSize_ the new audio buffer size to use
     */
    void setBufferSize(int bufferSize_);
    
    /** Update the AudioAnalysisManager with the host sampling frequency
     * @param fs the sampling frequency
     */
    void setSamplingFrequency(int fs);
    
    /** Update the AudioAnalysisManager with the host audio frame size
     * @param frameSize the audio frame size of the host
     */
    void setHostFrameSize(int frameSize);
    
    /** An array of Analysis objects */
    OwnedArray<Analysis> analyses;

    
private:
    
    /** Register all audio analysis algorithms that will be available in the plug-in */
    void addAudioAnalysisAlgorithms();
    
    /** The audio buffer size used by the plug-in to calculate audio analyses */
    int bufferSize;
    
    /** An AudioAnalysisBuffer object to manage audio buffers when new audio frames are received from the host */
    AudioAnalysisBuffer audioBuffer;
    
    /** An instance of the gist audio analysis library */
    Gist<float> gist;
    
    
    //=======================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalysisManager)
    //=======================================================================
};

#endif  // ANALYSISMANAGER_H_INCLUDED
