/*
  ==============================================================================

    OriginalPlotComponent.cpp
    Created: 3 Jul 2016 5:13:47pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "OriginalPlotComponent.h"
#include "PluginLookAndFeel.h"

//==============================================================================
OriginalPlotComponent::OriginalPlotComponent(SoundAnalyserAudioProcessor& _processor) : processor(_processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    plotHeight = 150;
    plotY = 40;
    
    startTimer (50);

}

OriginalPlotComponent::~OriginalPlotComponent()
{
}

void OriginalPlotComponent::paint (Graphics& g)
{
    PluginLookAndFeel::fillWithBackgroundTexture (g);
    g.setColour (Colour::fromRGBA(56, 61, 68,245));
    g.fillAll (Colour::fromRGBA(34, 34, 34,245));
    
    if (processor.analyser.currentAnalysisToPlotType == FloatOutput)
    {
        int N = processor.analyser.plotHistory.size();
        
        int plotX = (getWidth()- N)/2;
        
        
        g.fillRect(plotX, plotY, N, plotHeight);
        
        g.setColour(Colours::lightsteelblue);
        
        float previousValue = processor.analyser.plotHistory[0];
        
        // get the max value
        float maxValue = -10000;
        for (int i = 0;i < N;i++)
        {
            if (processor.analyser.plotHistory[i] > maxValue)
            {
                maxValue = processor.analyser.plotHistory[i];
            }
        }
        
        // do the plotting
        for (int i = 0;i < N-1;i++)
        {
            float currentValue = processor.analyser.plotHistory[i+1];
            
            int p1 = plotY + (plotHeight - ((previousValue/maxValue)*plotHeight));
            int p2 = plotY + (plotHeight - ((currentValue/maxValue)*plotHeight));
            
            g.setColour(Colours::lightsteelblue);
            g.drawLine(plotX+i,p1,plotX+i+1,p2);
            
            previousValue = currentValue;
        }
        
    }
    else if (processor.analyser.currentAnalysisToPlotType == VectorOutput)
    {
        int N = processor.analyser.vectorPlot.size();
        int plotWidth = 512;
        
        int plotX = (getWidth() - plotWidth) / 2;
        
        g.fillRect(plotX, plotY, plotWidth,plotHeight);
        
        g.setColour(Colours::greenyellow);
        
        float previousValue = processor.analyser.vectorPlot[0];
        
        // get the max value
        float maxValue = -10000;
        for (int i = 0;i < N;i++)
        {
            if (processor.analyser.vectorPlot[i] > maxValue)
            {
                maxValue = processor.analyser.vectorPlot[i];
            }
        }
        
        // do the plotting
        for (int i = 0;i < N-1;i++)
        {
            float currentValue = processor.analyser.vectorPlot[i+1];
            
            int p1 = plotY + (plotHeight - ((previousValue/maxValue)*plotHeight));
            int p2 = plotY + (plotHeight - ((currentValue/maxValue)*plotHeight));
            
            int x1 = i*round(512.0/((double)N-1.));
            int x2 = (i+1)*round(512.0/((double)N-1.));
            
            g.drawLine(plotX+x1,p1,plotX+x2,p2);
            
            previousValue = currentValue;
        }
        
    }
}

void OriginalPlotComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
