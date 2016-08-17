//=======================================================================
/** @file AnalysisModel.cpp
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

#include "ProcessorModel.h"

// instantiate static variables

const Identifier AnalyserProperties::Analyser("Analyser");
const Identifier AnalyserProperties::BufferSize("BufferSize");
const Identifier AnalyserProperties::SamplingFrequency("SamplingFrequency");

const Identifier AnalysisProperties::Analyses("Analyses");
const Identifier AnalysisProperties::Name("Name");
const Identifier AnalysisProperties::FFT::NumSamplesToSend("NumSamplesToSend");
const Identifier AnalysisProperties::MelFrequencySpectrum::NumBins("NumBins");



