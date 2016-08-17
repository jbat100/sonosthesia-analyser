//=======================================================================
/** @file MelFrequencySpectrum.h
 *  @brief The Mel Frequency Spectrum audio analysis module
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

#ifndef __Sound_Analyser__MelFrequencySpectrum__
#define __Sound_Analyser__MelFrequencySpectrum__

#include "AudioAnalysis.h"
#include "ProcessorModel.h"
#include "../GUI/Custom Analysis Components/MelFreqSpecComponent.h"


class MelFrequencySpectrum : public AudioAnalysis
{
public:
    
    //==============================================================================
    MelFrequencySpectrum(int frameSize,int samplingFrequency) : mfcc(frameSize, samplingFrequency)
    {
        numBins = defaultNumBins;
    }
    
    //==============================================================================
    String getName() override
    {
        return "Mel-frequency Spectrum";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> magnitudeSpectrum) override
    {
        mfccOutput = mfcc.melFrequencySpectrum(magnitudeSpectrum);
    }
    
    //==============================================================================
    std::vector<float> getAnalysisResultAsVector() override
    {
        return mfccOutput;
    }
    
    //==============================================================================
    void setSamplingFrequency(int fs) override
    {
        mfcc.setSamplingFrequency(44100);
    }
    
    //==============================================================================
    void setInputAudioFrameSize(int frameSize) override
    {
        mfcc.setFrameSize(frameSize);
    }
    
    void setNumCoefficients(int num) 
    {
        // local copy
        numBins = num;
        
        // set the number of coefficients in the mfcc object
        mfcc.setNumCoefficients(numBins);
    }
    
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("MelFrequencySpectrum");
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
        return "The magnitude spectrum mapped on to a Mel scale using a bank of triangular filters.";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A feature showing you how energy is distributed across the frequency range, on a scale related to human perception";
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
    void loadFromValueTree(ValueTree &tree) override
    {
        AudioAnalysis::loadFromValueTree(tree);
        // this property is unique to Mel Frequency Spectrum
        if (tree.hasProperty(AnalysisProperties::MelFrequencySpectrum::NumBins))
        {
            setNumCoefficients( tree[AnalysisProperties::MelFrequencySpectrum::NumBins] ); // default should be 13
        }
        else
        {
            setNumCoefficients( defaultNumBins );
        }
    }
    
    //==============================================================================
    ValueTree saveToValueTree() override
    {
        ValueTree tree = AudioAnalysis::saveToValueTree();
        
        // extra properties for Mel Frequency Spectrum
        tree.setProperty(AnalysisProperties::MelFrequencySpectrum::NumBins, numBins, nullptr);
        
        return tree;
    }
    
    int getNumBins()
    {
        return numBins;
    }
    
private:
    
    MFCC<float> mfcc;
    std::vector<float> mfccOutput;
    
    int numBins;
    
    static const int defaultNumBins = 13;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MelFrequencySpectrum)
};

#endif /* defined(__Sound_Analyser__MelFrequencySpectrum__) */
