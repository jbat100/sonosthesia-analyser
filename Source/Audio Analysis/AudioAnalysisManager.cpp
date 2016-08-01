//=======================================================================
/** @file AudioAnalysisManager.cpp
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

#include "AudioAnalysisManager.h"
#include "ProcessorSettings.h"

#include "../Libraries/speex/include/speex/speex_resampler.h"

//==============================================================================
// we need a 
AudioAnalysisManager::AudioAnalysisManager() :
    audioBuffer(DEFAULT_BUFFER_SIZE),
    gist(DEFAULT_BUFFER_SIZE, DEFAULT_SAMPLING_FREQUENCY)
    /*, port(8000), ipAddress("127.0.0.1"), mute(false) */
{
    
    // this function adds all algorithms that the plug-in will have access to
    addAudioAnalysisAlgorithms();
    
    setBufferSize(ProcessorSettings::getInstance()->getBufferSize());
    setHostFrameSize(ProcessorSettings::getInstance()->getHostFrameSize());
    setSamplingFrequency(ProcessorSettings::getInstance()->getSamplingFrequency());
    
    ProcessorSettings::getInstance()->add(this);
    
    currentAnalysisToPlotType = FloatOutput;

    vectorPlot.resize(512);
    plotHistory.resize(512);
    
    for (int i = 0;i < 512;i++)
    {
        plotHistory[i] = 0;
        vectorPlot[i] = 0;
    }
}

//==============================================================================
void AudioAnalysisManager::addAudioAnalysisAlgorithms()
{
    // !!!
    // please add new audio analyses in a group, per collection, and then in alphabetical order
    // by name as this is how they will appear on the selection dialog
    
    // GIST
    
    int bufferSize = ProcessorSettings::getInstance()->getBufferSize();
    // we should realy get the sampling frequency from here also, seems like it is always set to the default no matter what
    
    audioAnalyses.add(new FFTMagnitudeSpectrum());
    audioAnalyses.add(new MelFrequencySpectrum(bufferSize, DEFAULT_SAMPLING_FREQUENCY));
    audioAnalyses.add(new PeakEnergy());
    audioAnalyses.add(new Pitch(bufferSize, DEFAULT_SAMPLING_FREQUENCY));
    audioAnalyses.add(new RMS());
    audioAnalyses.add(new SpectralCentroid());
    audioAnalyses.add(new SpectralCrest());
    audioAnalyses.add(new SpectralDifference(bufferSize));
    audioAnalyses.add(new SpectralFlatness());
    audioAnalyses.add(new ZeroCrossingRate());
    
    // QMUL
    audioAnalyses.add(new SP_ChordDetector(bufferSize, DEFAULT_SAMPLING_FREQUENCY));
    audioAnalyses.add(new SP_Chromagram(bufferSize, DEFAULT_SAMPLING_FREQUENCY));

}

bool AudioAnalysisManager::shouldSendResults()
{
    return audioBuffer.isReady();
}

AudioAnalysis* AudioAnalysisManager::getAnalysisWithIdentifier(String identifier)
{
    for (int i = 0;i < audioAnalyses.size();i++)
    {
        if (audioAnalyses[i]->getIdentifier().toString() == identifier)
        {
            return audioAnalyses[i];
        }
    }
    
    return nullptr; 
}

//==============================================================================
void AudioAnalysisManager::analyseAudio(float* buffer,int numSamples)
{
    // add new audio frame to our larger buffer
    audioBuffer.addNewSamplesToBuffer(buffer,numSamples);
        
    if (audioBuffer.isReady())
    {
    
        gist.processAudioFrame(audioBuffer.buffer);
        
        for (int i = 0;i < audioAnalyses.size();i++)
        {
            if (audioAnalyses[i]->getRelayed())
            {
                if (audioAnalyses[i]->getOutputType() == FloatOutput)
                {
                    //float output = 0.0;
                    
                    if (audioAnalyses[i]->getInputType() == AudioBufferInput)
                    {
                        audioAnalyses[i]->performAnalysis(audioBuffer.buffer);
                    }
                    else if (audioAnalyses[i]->getInputType() == MagnitudeSpectrumInput)
                    {
                        audioAnalyses[i]->performAnalysis(gist.getMagnitudeSpectrum());
                    }
                    if (audioAnalyses[i]->resultReady())
                    {
                        // old plit and send settings
                        /*
                        output = audioAnalyses[i]->getAnalysisResultAsFloat();
                        if (audioAnalyses[i]->send && !mute)
                        {
                            OSCMessage m(OSCAddressPattern(audioAnalyses[i]->addressPattern));
                            m.addFloat32(output);
                            osc.send(m);
                        }
                        if (audioAnalyses[i]->plot)
                        {
                            updatePlotHistory(output);
                        }
                         */
                        
                    }
                }
                else if (audioAnalyses[i]->getOutputType() == VectorOutput)
                {
                    std::vector<float> output;
                    
                    if (audioAnalyses[i]->getInputType() == AudioBufferInput)
                    {
                       audioAnalyses[i]->performAnalysis(audioBuffer.buffer);
                    }
                    else if (audioAnalyses[i]->getInputType() == MagnitudeSpectrumInput)
                    {
                        audioAnalyses[i]->performAnalysis(gist.getMagnitudeSpectrum());
                    }
                    else
                    {
                        // failsafe!
                        output.resize(1);
                        output[0] = 0.0;
                    }
                    
                    if (audioAnalyses[i]->resultReady())
                    {
                        // old plot and send settings
                        
                        /*
                        output = audioAnalyses[i]->getAnalysisResultAsVector();
                        
                        if (audioAnalyses[i]->send && !mute)
                        {
                            OSCMessage m(OSCAddressPattern(audioAnalyses[i]->addressPattern));
                            for (int i = 0;i < output.size();i++)
                            {
                                m.addFloat32(output[i]);
                            }
                            osc.send(m);
                        }

                        if (audioAnalyses[i]->plot)
                        {
                            updateVectorPlot(output);
                        }
                         */
                    }
                }
            }
        }
    }
    
}


//==============================================================================

void AudioAnalysisManager::processorBufferSizeChanged(ProcessorSettings* settings)
{
    setBufferSize(settings->getBufferSize());
}

void AudioAnalysisManager::processorHostFrameSizeChanged(ProcessorSettings* settings)
{
    setHostFrameSize(settings->getHostFrameSize());
}

void AudioAnalysisManager::processorSamplingFrequencyChanged(ProcessorSettings* settings)
{
    setSamplingFrequency(settings->getSamplingFrequency());
}

//==============================================================================
void AudioAnalysisManager::setBufferSize(int bufferSize)
{
    // initialise the audio buffer
    audioBuffer.setBufferSize(bufferSize);
    
    gist.setAudioFrameSize(bufferSize);
    
    // -----------------------------------------------
    // now for some analysis specific initialisations
    
    for (int i = 0;i < audioAnalyses.size();i++)
    {
        audioAnalyses[i]->setInputAudioFrameSize(bufferSize);
    }
}

//==============================================================================
void AudioAnalysisManager::setSamplingFrequency(int fs)
{
    for (int i = 0;i < audioAnalyses.size();i++)
    {
        audioAnalyses[i]->setSamplingFrequency(fs);
    }
}

//==============================================================================
void AudioAnalysisManager::setHostFrameSize(int frameSize)
{
    
}


//==============================================================================
void AudioAnalysisManager::updatePlotHistory(float newSample)
{
    int N = plotHistory.size();
    
    for (int i = 0; i < N-1;i++)
    {
        plotHistory[i] = plotHistory[i+1];
    }
    
    plotHistory[N-1] = newSample;
}

//==============================================================================
void AudioAnalysisManager::clearPlotHistory()
{
    int N = plotHistory.size();
    
    for (int i = 0; i < N;i++)
    {
        plotHistory[i] = 0;
    }
    
}

//==============================================================================
std::vector<float> AudioAnalysisManager::resamplePlot(std::vector<float> v)
{
    std::vector<float> resampledSignal;
    resampledSignal.resize(512);
    
    float* inF;
    inF = new float[v.size()];
    float* outF;
    outF = new float[v.size()];
    
    for (int i = 0;i < v.size();i++)
    {
        inF[i] = (float) v[i];
    }
    
    SpeexResamplerState *resampler;
    
    int err = 0;
    
    resampler = speex_resampler_init(1, (spx_uint32_t) v.size(), 512, 0, &err);
    
    spx_uint32_t inLen = (spx_uint32_t) v.size();
    spx_uint32_t outLen = (spx_uint32_t) 512;
    
    err = speex_resampler_process_float(resampler, 0, inF, &inLen, outF, &outLen);
    
    for (int i = 0;i < resampledSignal.size();i++)
    {
        resampledSignal[i] = outF[i];
    }
    
    delete [] inF;
    delete [] outF;
    
    speex_resampler_destroy(resampler);
    
    return resampledSignal;
}

//==============================================================================
void AudioAnalysisManager::updateVectorPlot(std::vector<float> v)
{
    // if the vector is less than or equal to the
    // length of our plot window then we can just
    // use it as is
    if (v.size() <= 512)
    {
        vectorPlot.resize(v.size());
        
        for (int i = 0;i < v.size();i++)
        {
            vectorPlot[i] = v[i];
        }
    }
    else // otherwise, we have to downsample
    {
        vectorPlot.resize(512);
        vectorPlot = resamplePlot(v);
    }
}