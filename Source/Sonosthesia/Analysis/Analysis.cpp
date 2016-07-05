/*
  ==============================================================================

    Analysis.cpp
    Created: 5 Jul 2016 10:13:57pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "Analysis.h"

Analysis::Analysis()
{
    plot = false;
    send = false;
    
    vectorPlot.resize(512);
    plotHistory.resize(512);
    
    for (int i = 0;i < 512;i++)
    {
        plotHistory[i] = 0;
        vectorPlot[i] = 0;
    }
}
