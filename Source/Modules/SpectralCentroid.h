//=======================================================================
/** @file SpectralCentroid.h
 *  @brief The Spectral Centroid audio analysis module
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

#ifndef SoundAnalyser_SpectralCentroid_h
#define SoundAnalyser_SpectralCentroid_h

#include "AudioAnalysis.h"
#include <cmath>



class SpectralCentroid : public AudioAnalysis
{
public:
    
    //==============================================================================
    SpectralCentroid() : spectralCentroidOutputValue(0.0)
    {

    }
    
    //==============================================================================
    String getName() override
    {
        return "Spectral Centroid";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> magnitudeSpectrum) override
    {
        spectralCentroidOutputValue = fdf.spectralCentroid(magnitudeSpectrum);
    }
    
    //==============================================================================
    float getAnalysisResultAsFloat() override
    {
        return spectralCentroidOutputValue;
    }
        
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("SpectralCentroid");
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
        return "The centre of mass of the magnitude spectrum";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A feature correlated with the brightness of a sound";
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
    
    float spectralCentroidOutputValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralCentroid)
};

#endif
