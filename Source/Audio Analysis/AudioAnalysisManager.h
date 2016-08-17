//=======================================================================
/** @file AudioAnalysisManager.h
 *  @brief A class to manage audio input and all audio analysis modules
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

#ifndef _SOUNDANALYSER_AUDIOANALYSISMANAGER_
#define _SOUNDANALYSER_AUDIOANALYSISMANAGER_

//=======================================================================
#include "../JuceLibraryCode/JuceHeader.h"
#include "ProcessorSettings.h"
#include "AudioAnalysisBuffer.h"
#include "AudioAnalysis.h"
#include "../Libraries/Gist/src/Gist.h"

//=======================================================================
// import all audio analysis modules
#include "../Modules/RMS.h"
#include "../Modules/PeakEnergy.h"
#include "../Modules/ZeroCrossingRate.h"
#include "../Modules/SpectralCentroid.h"
#include "../Modules/SpectralCrest.h"
#include "../Modules/SpectralDifference.h"
#include "../Modules/SpectralFlatness.h"
#include "../Modules/FFTMagnitudeSpectrum.h"
#include "../Modules/Pitch.h"
#include "../Modules/MelFrequencySpectrum.h"
#include "../Modules/SP_Chromagram.h"
#include "../Modules/SP_ChordDetector.h"


//=======================================================================
/** A class to manage audio input and all audio analysis modules
 */
class AudioAnalysisManager : public ProcessorSettingsListnener {

public:
    /** Constructor */
    AudioAnalysisManager();
    
    /** Passes the audio buffer through a number of analysis algorithms
     * @param buffer the audio buffer containing the audio samples
     * @param numSamples the number of audio samples in the buffer
     */
    void analyseAudio(float* buffer,int numSamples);
    
    //=============================================
    // ProcessorSettingsListnener
    
    void processorBufferSizeChanged(ProcessorSettings* settings) override;
    void processorHostFrameSizeChanged(ProcessorSettings* settings) override;
    void processorSamplingFrequencyChanged(ProcessorSettings* settings) override;
    
    //=============================================
    // Analyses
    
    /** An array of AudioAnalysis objects */
    OwnedArray<AudioAnalysis> audioAnalyses;
    
    /** Sonosthesia add on, true if relay manager should send the results through OSC clients **/
    bool shouldSendResults();
    
    AudioAnalysis* getAnalysisWithIdentifier(String identifier);
    
    //=============================================
    // Plot related stuff, obsolete...
    
    /** Resets the plotHistory to zeros */
    void clearPlotHistory();
    
    /** The current audio analysis plot type */
    OutputType currentAnalysisToPlotType;
    
    /** A vector containing time domain data to be plotted in the plug-in GUI */
    std::vector<float> plotHistory;
    
    /** A vector containing the data to be plotted for an audio analysis algorithm that returns vectors */
    std::vector<float> vectorPlot;
    
private:
    
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
 
    /** Add a new sample to the plot history
     * @param newSample the new sample to add to the plot history
     */
    void updatePlotHistory(float newSample);
    
    /** Register all audio analysis algorithms that will be available in the plug-in */
    void addAudioAnalysisAlgorithms();
    
    /** Resamples a vector to the correct length for plotting */
    std::vector<float> resamplePlot(std::vector<float> v);
    
    /** Updates the vector plot with the latest vector result */
    void updateVectorPlot(std::vector<float> v);
    
    /** An AudioAnalysisBuffer object to manage audio buffers when new audio frames are received from the host */
    AudioAnalysisBuffer audioBuffer;
    
    /** An instance of the gist audio analysis library */
    Gist<float> gist;
    
    /*
     // old send settings, now replaced by relays, use ProcessorSettings singleton for buffer size
    OSCSender osc; // allows osc to be sent to a specific ip address and port number
    int bufferSize; // The audio buffer size used by the plug-in to calculate audio analyses
    int port; // The port to send to
    String ipAddress; // The remote host IP address to send to
    bool mute;
     */
    
    //=======================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioAnalysisManager)
    //=======================================================================
};

#endif /* defined(__SoundAnalyser__AudioAnalysisManager__) */
