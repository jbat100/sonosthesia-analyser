//=======================================================================
/** @file SP_ChordDetector.h
 *  @brief The Stark and Plumbley Chord Detector module
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

#ifndef Sound_Analyser_SP_ChordDetector_h
#define Sound_Analyser_SP_ChordDetector_h

#include "../Audio Analysis/AudioAnalysis.h"
#include "../Libraries/Stark-Plumbley/Chromagram.h"
#include "../Libraries/Stark-Plumbley/ChordDetector.h"

class SP_ChordDetector : public AudioAnalysis
{
public:
    
    //==============================================================================
    SP_ChordDetector(int frameSize, int samplingFrequency) : chroma(frameSize, samplingFrequency)
    {

    }
    
    //==============================================================================
    String getName() override
    {
        return "Chord Detector";
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
    float getAnalysisResultAsFloat() override
    {
        std::vector<double> chromagram = chroma.getChromagram();
        
        chord.detectChord(chromagram);
        
        return (float) chord.rootNote;
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
        return Identifier("SP_ChordDetector");
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
        return "The root note from the chord detection algorithm presented by Stark and Plumbley (2009)";
    }
    
    //==============================================================================
    String getSimpleDescription() override
    {
        return "An estimation of the root note (C, C#, D, etc) of the input audio signal";
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
    
    Chromagram chroma;
    ChordDetector chord;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SP_ChordDetector)
};

#endif
