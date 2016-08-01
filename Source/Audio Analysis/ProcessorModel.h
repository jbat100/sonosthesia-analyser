//=======================================================================
/** @file AnalysisModel.h
 *  @brief The ValueTree model for the Sound Analyser plug-in
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

#ifndef _SOUNDANALYSER_PROCESSORMODEL_
#define _SOUNDANALYSER_PROCESSORMODEL_

#include "../JuceLibraryCode/JuceHeader.h"

//======================================================================
struct AnalysisProperties
{
    static const Identifier Analyses;           /**  The parent of all analyses */
    
    static const Identifier Name;               /**  The audio analysis name identifier */
    
    struct FFT {
        static const Identifier NumSamplesToSend;
    };
    
    struct MelFrequencySpectrum {
        static const Identifier NumBins;
    };
    
};

//======================================================================
/** Defines the core structure and properties of the Sound Analyser plug-in */
struct AnalyserProperties {
    
    static const Identifier Analyser;                           /**<  Root plugin identifier */
    static const Identifier BufferSize;                         
    static const Identifier SamplingFrequency;

};

#endif /* defined(__SoundAnalyser__AnalysisModel__) */
