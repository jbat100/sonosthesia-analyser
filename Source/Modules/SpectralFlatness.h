//=======================================================================
/** @file SpectralFlatness.h
 *  @brief The Spectral Flatness audio analysis module
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

#ifndef _SOUNDANALYSER_SPECTRALFLATNESS_
#define _SOUNDANALYSER_SPECTRALFLATNESS_

#include "AudioAnalysis.h"
#include <cmath>

class SpectralFlatness : public AudioAnalysis
{
public:
    
    //==============================================================================
    SpectralFlatness() : spectralFlatnessOutputValue(0.0)
    {
        
    }
    
    //==============================================================================
    String getName() override
    {
        return "Spectral Flatness";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> magnitudeSpectrum) override
    {
        spectralFlatnessOutputValue = fdf.spectralFlatness(magnitudeSpectrum);
    }
    
    //==============================================================================
    float getAnalysisResultAsFloat() override
    {
        return spectralFlatnessOutputValue;
    }
    
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("SpectralFlatness");
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
        return "The geometric mean of the magnitude spectrum divided by the arithmetic mean";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "An indication of how 'noise-like' the signal is";
    }
    
    //==============================================================================
    OutputType getOutputType() override
    {
        return FloatOutput;
    }
    
    //==============================================================================
    InputType getInputType() override
    {
        return MagnitudeSpectrumInput;
    }
    
private:
    
    CoreFrequencyDomainFeatures<float> fdf;
    
    float spectralFlatnessOutputValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralFlatness)
};

#endif
