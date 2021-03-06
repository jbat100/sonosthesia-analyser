//=======================================================================
/** @file AudioAnalysis.h
 *  @brief The base class for all audio analysis modules
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

#ifndef _SOUNDANALYSER_AUDIOANALYSIS_
#define _SOUNDANALYSER_AUDIOANALYSIS_

#include <vector>
#include <string>
#include "ProcessorModel.h"
#include "ProcessorSettings.h"
#include "../Libraries/Gist/src/Gist.h"

class AudioAnalysis;

class AudioAnalysisListener {
    
public:
    
    virtual ~AudioAnalysisListener() {}
    
    virtual void audioAnalysisChanged(AudioAnalysis* analysis) = 0;
    
};

//=======================================================================
/** The InputType for the audio analysis module.
 
    This will determine the nature of the vector passed to performAnalysis()
 */
enum InputType
{
    AudioBufferInput,
    MagnitudeSpectrumInput
};

//=======================================================================
/** The OutputType for the audio analysis module */
enum OutputType
{
    FloatOutput,
    VectorOutput
};

//=======================================================================
/** The base class for all audio analysis modules. 
 
    To create a new AudioAnalysis module, just extend this class.
 */
class AudioAnalysis : public ListenerList<AudioAnalysisListener>, public ProcessorSettingsListnener
{
public:
    
    AudioAnalysis() : relayed(false) {
        // react to processor settings changes if necessary
        ProcessorSettings::getInstance()->add(this);
    }
    
    virtual ~AudioAnalysis() {}
    
    //==============================================================================
    
    
    /** @returns the InputType that should be used by the AudioAnalysis.
        
        This will be one of the options in the InputType enum, and it will determine
        what type of data will be passed to performAnalysis()
        
        @see performAnalysis()
     */
    virtual InputType getInputType() = 0;
    
    
    /** @returns the OutputType to be used by the AudioAnalysis 
     
        This will be one of the options in the OutputType enum, and it will require you
        to implement a specific 'get' method, e.g. getAnalysisResultAsFloat() or
        getAnalysisResultAsVector().
     
     @see performAnalysis()
     */
    virtual OutputType getOutputType() = 0;
    
    
    /** @returns the Identifier that describes the audio analysis module
     
        This should be a JUCE Identifier - i.e. a String with no spaces, containing
        only the following characters:
     
        abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-:#@$%. 
     
        This Identifier should also be different to all other audio analysis module Identifiers
    */
    virtual Identifier getIdentifier() = 0;
    
    /** @returns the name of the Audio Analysis module as a string */
    virtual String getName() = 0;
    
    /** @returns an Identifier describing the collection to which the audio analysis module belongs */
    virtual Identifier getCollectionIdentifier() = 0;
    
    /** @returns the name of the collection to which the AudioAnalysis module belongs */
    virtual String getCollectionName() = 0;
    
    /** @returns the author of the audio analysis algorithm as a String */
    virtual String getAuthorString() = 0;
    
    /** @returns a String containing a technical description of the audio analysis module */
    virtual String getTechnicalDescription() = 0;

    /** @returns a String containing a simple description of the audio analysis module, for non-expert users */
    virtual String getSimpleDescription() = 0;
    
    
    /** The method that will be called when the audio analysis module should calculate its result. 
     
     The nature of the buffer passed to the function is determined by the return value of getInputType()
     
     @param buffer a buffer of samples in either the time or frequency domain, according to getInputType()
     
     @see getInputType()
     */
    virtual void performAnalysis(std::vector<float> buffer) = 0;
    
    //==============================================================================
    
    /** @returns the audio analysis result as a single float. Should be implemented by AudioAnalysis modules for which the return
     type of getOutputType() is FloatOutput from the OutputType enum.
     */
    virtual float getAnalysisResultAsFloat()
    {
        return 0;
    }
    
    /** @returns the audio analysis result as a vector of floats. Should be implemented by AudioAnalysis modules for which the return
     type of getOutputType() is VectorOutput from the OutputType enum.
     */
    virtual std::vector<float> getAnalysisResultAsVector()
    {
        std::vector<float> v;
        return v;
    }

    
    /** Indicates whether the audio analysis result is ready to be returned from one of the 'get' functions
        (e.g. getAnalysisResultAsFloat() ). By default this always returns true, but if you want to implement
        an audio analysis module which doesn't return a result from every buffer then you can override this
        function to make it dependent on other circumstances related to your algorithm */
    virtual bool resultReady()
    {
        return true;
    }
    
    /** Override this function if your AudioAnalysis object needs to do something specific when the sampling frequency changes */
    virtual void setSamplingFrequency(int fs)
    {
        
    }
    /** Override this function if your AudioAnalysis object needs to do something specific when the host input audio frame size changes */    
    virtual void setInputAudioFrameSize(int frameSize)
    {
        
    }
    
    //==============================================================================
    
    /** Save state to a value tree */
    
    virtual ValueTree saveToValueTree()
    {
        std::cout << "Saving state for " << getIdentifier().toString() << "\n";
        ValueTree tree(getIdentifier());
        tree.setProperty(AnalysisProperties::Name, getName(), nullptr);
        return tree;
    }
    
    /** Load state from a value tree
     
        @param analysisTree a ValueTree node representing the audio analysis module
     
     */
    virtual void loadFromValueTree(ValueTree &tree)
    {
        if (tree.getType() != getIdentifier())
        {
            std::cerr << "AudioAnalysis unexpected identifier " << tree.getType().toString();
            std::cerr << ", expected " << getIdentifier().toString() << "\n";
        }
        else
        {
            std::cout << "Loading state for " << getIdentifier().toString() << "\n";
        }
    }
    
    void setRelayed(bool _relayed);
    bool getRelayed();
    
private:
    
    /** Sonosthesia: indicates whether the analysis is used by at least one relay **/
    bool relayed;
    
};

#endif /* defined(__SoundAnalyser__Analysis__) */
