//=======================================================================
/** @file FFTComponent.cpp
 *  @brief A custom component for the FFT Magnitude Spectrum module
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

#include "FFTComponent.h"

#include "../../Modules/FFTMagnitudeSpectrum.h"
#include "../../Sonosthesia/Core/Theme.h"

//==============================================================================
FFTComponent::FFTComponent(AudioAnalysis* _analysis) : SimpleAnalysisComponent(_analysis)
{
    jassert(dynamic_cast<FFTMagnitudeSpectrum*>(_analysis) != nullptr);
    
    setSize (580, 30);
    
    numFFTSamplesText.setText("Samples", dontSendNotification);
    Appearence::theme()->label(numFFTSamplesText);
    addAndMakeVisible(&numFFTSamplesText);
    
    numFFTSamples.setColour(Label::textColourId, Colours::black);
    numFFTSamples.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    numFFTSamples.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    numFFTSamples.setEditable(true);
    addAndMakeVisible(&numFFTSamples);
    
    numFFTSamples.addListener(this);
    
    refresh();
    
}

//==============================================================================
void FFTComponent::resized()
{
    SimpleAnalysisComponent::resized();
    
    numFFTSamplesText.setBounds(400, yOffset, 70, 20);
    numFFTSamples.setBounds(480, yOffset,40,20);
}

void FFTComponent::refresh()
{
    FFTMagnitudeSpectrum* fft = dynamic_cast<FFTMagnitudeSpectrum*>(getAudioAnalysis());
    
    if (fft)
    {
        numFFTSamples.setText(String(fft->getNumSamplesToSend()), dontSendNotification);
    }
}

//==============================================================================
void FFTComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &numFFTSamples)
    {
        int numSamples = numFFTSamples.getTextValue().getValue();
        FFTMagnitudeSpectrum* fft = dynamic_cast<FFTMagnitudeSpectrum*>(getAudioAnalysis());
        if (fft)
        {
            int result = fft->setNumFFTSamplesToSend(numSamples);
            if (result != numSamples)
            {
                // error message? fft size cannot be more than half of buffer size
                numFFTSamples.setText(String(result), dontSendNotification);
            }
        }
        else
        {
            std::cerr << "FFTComponent unexpected analysis\n";
        }
    }
}


