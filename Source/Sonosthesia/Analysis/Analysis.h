/*
  ==============================================================================

    Analysis.h
    Created: 5 Jul 2016 10:13:57pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef ANALYSIS_H_INCLUDED
#define ANALYSIS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "../../Audio Analysis/AnalysisModel.h"

class Analysis {
    
public:
    
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
    
    /** Destructor */
    virtual ~Analysis()
    {
        
    }
    
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
    
    /** @returns the core address pattern that will be used to form OSC messages when sending the audio analysis
     module data. An example might be "/rms"
     */
    virtual std::string getCoreAddressPattern() = 0;
    
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
    
    /** Creates the audio analysis module's ValueTree node.
     
     Override this if you need to create custom properties for your module
     */
    virtual ValueTree createAnalysisTree()
    {
        ValueTree tree(getIdentifier());
        tree.setProperty(AnalysisProperties::send, 0, nullptr);
        tree.setProperty(AnalysisProperties::plot, 0, nullptr);
        tree.setProperty(AnalysisProperties::name, getName(), nullptr);
        return tree;
    }
    
    /** Initialises internal variables based upon the audio analysis ValueTree
     
     Override this if you have extra parameters for the analysis algorithm you are developing as you
     will need to initialise them from the ValueTree
     
     @param analysisTree a ValueTree node representing the audio analysis module
     
     */
    virtual void initialise(ValueTree &analysisTree)
    {
        send = analysisTree[AnalysisProperties::send];
        plot = analysisTree[AnalysisProperties::plot];
    }
    
    
    /** Indicates whether the module should update the plotting vectors */
    bool plot;
    
    /** Indicates whether the module should send its result by OSC */
    bool send;
    
    /** A vector containing time domain data to be plotted in the plug-in GUI */
    std::vector<float> plotHistory;
    
    /** A vector containing the data to be plotted for an audio analysis algorithm that returns vectors */
    std::vector<float> vectorPlot;
    
    /** Add a new sample to the plot history
     * @param newSample the new sample to add to the plot history
     */
    void updatePlotHistory(float newSample);
    
    /** Resamples a vector to the correct length for plotting */
    std::vector<float> resamplePlot(std::vector<float> v);
    
    /** Updates the vector plot with the latest vector result */
    void updateVectorPlot(std::vector<float> v);
    
};


#endif  // ANALYSIS_H_INCLUDED
