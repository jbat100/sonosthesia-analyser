//=======================================================================
/** @file MelFreqSpecComponent.cpp
 *  @brief A custom component for the MelFrequencySpectrum module
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

#include "MelFreqSpecComponent.h"

#include "../../Modules/MelFrequencySpectrum.h"
#include "../../Sonosthesia/Core/Theme.h"

//==============================================================================
MelFreqSpecComponent::MelFreqSpecComponent(AudioAnalysis* _analysis) : SimpleAnalysisComponent(_analysis)
{
    jassert(dynamic_cast<MelFrequencySpectrum*>(_analysis) != nullptr);
    
    setSize (580, 30);
   
    numMelBinsText.setText("Bins", dontSendNotification);
    Appearence::theme()->label(numMelBinsText);
    addAndMakeVisible(&numMelBinsText);
    
    Appearence::theme()->field(numMelBins);
    numMelBins.setEditable(true);
    addAndMakeVisible(&numMelBins);
    
    numMelBins.addListener(this);
    
    refresh();
}

void MelFreqSpecComponent::resized()
{
    SimpleAnalysisComponent::resized();
    
    numMelBinsText.setBounds(400, yOffset, 70, 20);
    numMelBins.setBounds(480, yOffset, 40, 20);
}

//==============================================================================
void MelFreqSpecComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &numMelBins)
    {
        int numBins = numMelBins.getTextValue().getValue();
        
        MelFrequencySpectrum* spectrum = dynamic_cast<MelFrequencySpectrum*>(getAudioAnalysis());
        
        if (spectrum)
        {
            spectrum->setNumCoefficients(numBins);
        }
        else
        {
            std::cerr << "MelFreqSpecComponent unexpected analysis\n";
        }
    }
}

void MelFreqSpecComponent::refresh()
{
    MelFrequencySpectrum* mel = dynamic_cast<MelFrequencySpectrum*>(getAudioAnalysis());
    
    if (mel)
    {
        numMelBins.setText(String(mel->getNumBins()), dontSendNotification);
    }
}
