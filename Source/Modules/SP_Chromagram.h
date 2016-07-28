//=======================================================================
/** @file SP_Chromagram.h
 *  @brief The Stark and Plumbley Chromagram extraction algorithm module
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

#ifndef Sound_Analyser_SP_Chromagram_h
#define Sound_Analyser_SP_Chromagram_h

#include "AudioAnalysis.h"
#include "../Libraries/Stark-Plumbley/Chromagram.h"

class SP_Chromagram : public AudioAnalysis 
{
public:
    
    //==============================================================================
    SP_Chromagram(int frameSize, int samplingFrequency) : chroma(frameSize, samplingFrequency)
    {

    }
    
    //==============================================================================
    String getName() override
    {
        return "Chromagram";
    }
    
    //==============================================================================
    void performAnalysis(std::vector<float> audioFrame) override
    {
        std::vector<double> doublePrecisionBuffer(audioFrame.size());
        
        for (int i = 0;i < doublePrecisionBuffer.size();i++)
        {
            doublePrecisionBuffer[i] = (double) audioFrame[i];
        }
        
        chroma.processAudioFrame(doublePrecisionBuffer);
    }
    
    //==============================================================================
    std::vector<float> getAnalysisResultAsVector() override
    {
        std::vector<double> chromagram = chroma.getChromagram();
        
        std::vector<float> chromaFloat(12);
        
        for (int i = 0;i < 12;i++)
        {
            chromaFloat[i] = (float) chromagram[i];
        }
        
        return chromaFloat;
    }
    
    //==============================================================================
    bool resultReady() override
    {
        return chroma.isReady();
    }
    
    //==============================================================================
    void setSamplingFrequency(int fs) override
    {
        chroma.setSamplingFrequency(fs);
    }
    
    //==============================================================================
    void setInputAudioFrameSize(int frameSize) override
    {
        chroma.setInputAudioFrameSize(frameSize);
    }
    
    //==============================================================================
    Identifier getIdentifier() override
    {
        return Identifier("SP_Chromagram");
    }
    
    //==============================================================================
    Identifier getCollectionIdentifier() override
    {
        return Identifier("C4DMQMUL");
    }
    
    //==============================================================================
    String getCollectionName() override
    {
        return "Queen Mary Univ. of London";
    }
    
    //==============================================================================
    String getAuthorString() override
    {
        return "Adam Stark & Mark Plumbley";
    }
    
    //==============================================================================
    String getTechnicalDescription() override
    {
        return "The chromagram from the real-time chord detection algorithm presented by Stark and Plumbley (2009)";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "A 12-element vector, indicating how much energy there is in each pitch class - how much 'C', how much 'C#', etc";
    }
    
    //==============================================================================
    OutputType getOutputType() override
    {
        return VectorOutput;
    }
    
    //==============================================================================
    InputType getInputType() override
    {
        return AudioBufferInput;
    }
    
private:
    
    Chromagram chroma;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SP_Chromagram)
};


#endif
