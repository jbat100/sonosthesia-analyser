//=======================================================================
/** @file SpectralDifference.h
 *  @brief The Spectral Difference audio analysis module
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

#ifndef SoundAnalyser_SpectralDifference_h
#define SoundAnalyser_SpectralDifference_h

class SpectralDifference : public AudioAnalysis
{
public:
    
    //==============================================================================
    SpectralDifference(int frameSize) : spectralDifferenceOutputValue(0.0), odf(frameSize)
    {

    }
    
    //==============================================================================
    String getName() override
    {
        return "Spectral Difference";
    }
        
    //==============================================================================
    void performAnalysis(std::vector<float> magnitudeSpectrum) override
    {
        spectralDifferenceOutputValue = odf.spectralDifference(magnitudeSpectrum);
    }
    
    //==============================================================================
    float getAnalysisResultAsFloat() override
    {
        return spectralDifferenceOutputValue;
    }
    
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("SpectralDifference");
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
        return "The sum of the absolute value of the bin-wise difference between consecutive magnitude spectra";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A feature showing peaks whenever there are sharp changes in a sound, e.g. at the start of notes";
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
    
    float spectralDifferenceOutputValue;
    OnsetDetectionFunction<float> odf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralDifference)

};

#endif
