//=======================================================================
/** @file SimpleAnalysisComponent.cpp
 *  @brief The basic component for an audio analysis module. Can be extended
 * to create custom components
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

#include "SimpleAnalysisComponent.h"

#include "../Sonosthesia/Core/Theme.h"

const int SimpleAnalysisComponent::yOffset = 5;

//==============================================================================
SimpleAnalysisComponent::SimpleAnalysisComponent(AudioAnalysis* _analysis) : analysis(_analysis)
{
    setSize (580, 30);
    
    jassert(analysis != nullptr);
    
    addAndMakeVisible(activityIndicator);
    updateActivityIndicator();
    
    nameLabel.setText(analysis->getName(), dontSendNotification);
    addAndMakeVisible(&nameLabel);
    Appearence::theme()->label(nameLabel);
    nameLabel.setJustificationType(Justification::verticallyCentred | Justification::left);
}

//==============================================================================
void SimpleAnalysisComponent::resized()
{
    activityIndicator.setBounds(30, yOffset, 80, 20);
    nameLabel.setBounds(120, yOffset, 200, 20);
}


//==============================================================================
void SimpleAnalysisComponent::paint(Graphics& g)
{
    int hmargin = 10;
    
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    
    b.setX(hmargin);
    b.setWidth( b.getWidth() - (hmargin*2) );
    b.setHeight( b.getHeight() - 10);
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(b, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(b.reduced(1), 5);
}

void SimpleAnalysisComponent::reload()
{
    updateActivityIndicator();
}

AudioAnalysis* SimpleAnalysisComponent::getAudioAnalysis()
{
    return analysis;
}

void SimpleAnalysisComponent::audioAnalysisChanged(AudioAnalysis* analysis)
{
    updateActivityIndicator();
}

void SimpleAnalysisComponent::updateActivityIndicator()
{
    if (analysis != nullptr)
    {
        if (analysis->getRelayed())
        {
            Appearence::theme()->indicator(activityIndicator, Theme::Primary);
            activityIndicator.setText("Active", dontSendNotification);
        }
        else
        {
            Appearence::theme()->indicator(activityIndicator, Theme::Background);
            activityIndicator.setText("Inactive", dontSendNotification);
        }
    }
    else
    {
        Appearence::theme()->indicator(activityIndicator, Theme::Warning);
        activityIndicator.setText("Unknown", dontSendNotification);
    }
}


