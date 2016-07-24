//=======================================================================
/** @file MelFreqSpecComponent.h
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

#ifndef __SoundAnalyser__MelFreqSpecComponent__
#define __SoundAnalyser__MelFreqSpecComponent__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../../Audio Analysis/AnalysisModel.h"
#include "../SimpleAnalysisComponent.h"

class MelFreqSpecComponent : public SimpleAnalysisComponent, public Label::Listener {
    
public:
    
    MelFreqSpecComponent(AudioAnalysis* _analysis);

    void resized() override;
     
    void labelTextChanged (Label* labelThatHasChanged) override;
    
private:
    
    Label numMelBinsText;
    Label numMelBins;
    
    //======================================================================//
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MelFreqSpecComponent)
    //======================================================================//
};

#endif /* defined(__SoundAnalyser__MelFreqSpecComponent__) */
