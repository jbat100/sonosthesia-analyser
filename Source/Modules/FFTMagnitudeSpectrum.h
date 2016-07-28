//=======================================================================
/** @file FFTMagnitudeSpectrum.h
 *  @brief The FFT Magnitude Spectrum audio analysis module
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

#ifndef SoundAnalyser_FFTMagnitudeSpectrum_h
#define SoundAnalyser_FFTMagnitudeSpectrum_h

#include "AudioAnalysis.h"
#include "../GUI/Custom Analysis Components/FFTComponent.h"
#include <cmath>

class FFTMagnitudeSpectrum : public AudioAnalysis
{
public:
    
    //==============================================================================
    FFTMagnitudeSpectrum()
    {        
        // initialise
        numSamplesToSend = 512;
    }
    
    //==============================================================================
    String getName() override
    {
        return "FFT Magnitude Spectrum";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> magnitudeSpectrum) override
    {
        magnitudeSpectrumResult.resize(numSamplesToSend);
        
        if (magnitudeSpectrumResult.size() <= magnitudeSpectrum.size())
        {
            for (int i = 0;i < magnitudeSpectrumResult.size();i++)
            {
                magnitudeSpectrumResult[i] = magnitudeSpectrum[i];
            }
        }
        else // <--- THIS SHOULDN'T HAPPEN
        {
            for (int i = 0;i < magnitudeSpectrum.size();i++)
            {
                magnitudeSpectrumResult[i] = magnitudeSpectrum[i];
            }
            
            for (int i = magnitudeSpectrum.size();i < magnitudeSpectrumResult.size();i++)
            {
                magnitudeSpectrumResult[i] = 0.0;
            }
        }
    }
    
    //==============================================================================
    std::vector<float> getAnalysisResultAsVector() override
    {
        return magnitudeSpectrumResult;
    }
        
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("FFT");
    }
    
    //==============================================================================
    Identifier getCollectionIdentifier() override
    {
        return Identifier("Gist");
    }
    
    //==============================================================================
    String getCollectionName() override
    {
        return "Gist";
    }
    
    //==============================================================================
    String getAuthorString() override
    {
        return "Adam Stark";
    }
    
    //==============================================================================
    String getTechnicalDescription() override
    {
        return "The magnitude spectrum calculated from the Fourier transform. The number of samples to display can be set via the user interface.";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A feature showing you how energy is distributed across the frequency range, on a linear scale";
    }
    
    //==============================================================================
    OutputType getOutputType() override
    {
        return VectorOutput;
    }
    
    //==============================================================================
    InputType getInputType() override
    {
        return MagnitudeSpectrumInput;
    }
    
    //==============================================================================
    void setInputAudioFrameSize(int frameSize) override
    {
        // if our number of samples to send parameter is larger
        // than the number of magnitude spectrum samples, then
        // automatically adjust
        if ((frameSize/2) < numSamplesToSend)
        {
            numSamplesToSend = frameSize/2;
        }
    }
    
    //===============================================================================
    void setNumFFTSamplesToSend(int numSamples)
    {
        numSamplesToSend = numSamples;
    }
    
    //==============================================================================
    /** overriding initialise here as we have extra fields! */
    void loadFromValueTree(ValueTree &tree) override
    {
        AudioAnalysis::loadFromValueTree(tree);
        numSamplesToSend = tree[AnalysisProperties::FFT::numSamplesToSend]; // default should be 512
    }
    
    //==============================================================================
    ValueTree saveToValueTree() override
    {
        ValueTree tree = AudioAnalysis::saveToValueTree();
        // extra properties for FFT
        tree.setProperty(AnalysisProperties::FFT::numSamplesToSend, numSamplesToSend, nullptr);
        return tree;
    }
    
private:
    
    int numSamplesToSend;
    
    std::vector<float> magnitudeSpectrumResult;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FFTMagnitudeSpectrum)
};

#endif
