//=======================================================================
/** @file FFTComponent.h
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

#ifndef __SoundAnalyser__FFTComponent__
#define __SoundAnalyser__FFTComponent__

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../SimpleAnalysisComponent.h"

class FFTComponent : public SimpleAnalysisComponent, public Label::Listener {
    
public:
    FFTComponent(AudioAnalysis* _analysis);
    
    void resized() override;
    
    void refresh();
    
    void labelTextChanged (Label* labelThatHasChanged) override;
    
private:
    
    Label numFFTSamplesText;
    Label numFFTSamples;
    
    //======================================================================//
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTComponent)
    //======================================================================//
};

#endif /* defined(__SoundAnalyser__FFTComponent__) */
