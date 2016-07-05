/*
  ==============================================================================

    AnalysisManager.cpp
    Created: 5 Jul 2016 9:53:15pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/


#include "AnalysisManager.h"
#include "../../Libraries/speex/include/speex/speex_resampler.h"

//==============================================================================
AnalysisManager::AnalysisManager(int bufferSize_) :
    bufferSize(bufferSize_),
    audioBuffer(bufferSize),
    gist(bufferSize, DEFAULT_SAMPLING_FREQUENCY)
{
    setBufferSize(bufferSize);
    
    // this function adds all algorithms that the plug-in will have access to
    addAudioAnalysisAlgorithms();
    
}

//==============================================================================
void AnalysisManager::addAudioAnalysisAlgorithms()
{
    // !!!
    // please add new audio analyses in a group, per collection, and then in alphabetical order
    // by name as this is how they will appear on the selection dialog
    
    // GIST
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
    audioAnalyses.add(new SP_ChordDetector(bufferSize,DEFAULT_SAMPLING_FREQUENCY));
    audioAnalyses.add(new SP_Chromagram(bufferSize,DEFAULT_SAMPLING_FREQUENCY));
    
}

//==============================================================================
void AnalysisManager::analyseAudio(float* buffer,int numSamples)
{
    // add new audio frame to our larger buffer
    audioBuffer.addNewSamplesToBuffer(buffer,numSamples);
    
    if (audioBuffer.isReady())
    {
        
        gist.processAudioFrame(audioBuffer.buffer);
        
        for (int i = 0;i < audioAnalyses.size();i++)
        {
            if (audioAnalyses[i]->send || audioAnalyses[i]->plot)
            {
                if (audioAnalyses[i]->getOutputType() == FloatOutput)
                {
                    
                    float output = 0.0;
                    
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
                        output = audioAnalyses[i]->getAnalysisResultAsFloat();
                        
                        if (audioAnalyses[i]->send)
                        {
                            OSCMessage m(OSCAddressPattern(audioAnalyses[i]->addressPattern));
                            
                            m.addFloat32(output);
                            
                            osc.send(m);
                        }
                        
                        if (audioAnalyses[i]->plot)
                        {
                            updatePlotHistory(output);
                        }
                        
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
                        output = audioAnalyses[i]->getAnalysisResultAsVector();
                        
                        if (audioAnalyses[i]->send)
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
                    }
                }
                
                
            }
        }
    }
    
}

//==============================================================================
void AnalysisManager::updatePlotHistory(float newSample)
{
    int N = plotHistory.size();
    
    for (int i = 0; i < N-1;i++)
    {
        plotHistory[i] = plotHistory[i+1];
    }
    
    plotHistory[N-1] = newSample;
}

//==============================================================================
void AnalysisManager::clearPlotHistory()
{
    int N = plotHistory.size();
    
    for (int i = 0; i < N;i++)
    {
        plotHistory[i] = 0;
    }
    
}

//==============================================================================
void AnalysisManager::setAnalyserIdString(std::string analyserId)
{
    std::string idWithSlash("/");
    
    idWithSlash = idWithSlash.append(analyserId);
    
    for (int i = 0;i < audioAnalyses.size();i++)
    {
        audioAnalyses[i]->buildAddressPatternFromId(idWithSlash);
    }
}

//==============================================================================
void AnalysisManager::setBufferSize(int bufferSize_)
{
    // store the buffer size
    bufferSize = bufferSize_;
    
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
void AnalysisManager::setOSCPort(int oscPort)
{
    port = oscPort;
    osc.connect(ipAddress, port);
}

//==============================================================================
void AnalysisManager::setIPAddress(std::string remoteHostIPAddress)
{
    ipAddress = remoteHostIPAddress;
    osc.connect(ipAddress, port);
}

//==============================================================================
void AnalysisManager::setSamplingFrequency(int fs)
{
    for (int i = 0;i < audioAnalyses.size();i++)
    {
        audioAnalyses[i]->setSamplingFrequency(fs);
    }
}

//==============================================================================
void AnalysisManager::setHostFrameSize(int frameSize)
{
    AnalysisModel::currentHostFrameSize = frameSize;
}

//==============================================================================
std::vector<float> AnalysisManager::resamplePlot(std::vector<float> v)
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
void AnalysisManager::updateVectorPlot(std::vector<float> v)
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