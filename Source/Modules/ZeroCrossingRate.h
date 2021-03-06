//=======================================================================
/** @file ZeroCrossingRate.h
 *  @brief The Zero Crossing Rate audio analysis module
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

#ifndef SoundAnalyser_ZeroCrossingRate_h
#define SoundAnalyser_ZeroCrossingRate_h

#include "AudioAnalysis.h"
#include <cmath>

class ZeroCrossingRate : public AudioAnalysis
{
public:
    
    //==============================================================================
    ZeroCrossingRate() : zcrOutputValue(0.0)
    {

    }
    
    //==============================================================================
    String getName() override
    {
        return "Zero Crossing Rate";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> audioFrame) override
    {
        zcrOutputValue = tdf.zeroCrossingRate(audioFrame);
    }
    
    //==============================================================================
    float getAnalysisResultAsFloat() override
    {
        return zcrOutputValue;
    }

    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("ZeroCrossingRate");
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
        return "The count of zero crossings in each observed frame";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A feature giving an indication of the brightness of a sound";
    }
    
    //==============================================================================
    OutputType getOutputType() override
    {
        return FloatOutput;
    }
    
    //==============================================================================
    InputType getInputType() override
    {
        return AudioBufferInput;
    }
    
private:
    
    float zcrOutputValue;
    CoreTimeDomainFeatures<float> tdf;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroCrossingRate)
};


#endif
