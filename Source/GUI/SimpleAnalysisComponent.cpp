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
    
    //String name = analysisTree[AnalysisProperties::name];
    //nameLabel.setText(name, dontSendNotification);
    
    jassert(analysis != nullptr);
    
    addAndMakeVisible(activityIndicator);
    updateActivityIndicator();
    
    nameLabel.setText(analysis->getName(), dontSendNotification);
    addAndMakeVisible(&nameLabel);
    Appearence::theme()->label(nameLabel);
    nameLabel.setColour(Label::ColourIds::backgroundColourId, Colours::grey);
    nameLabel.setJustificationType(Justification::verticallyCentred | Justification::left);
    
    /*
     
     sendButton.setButtonText("Send");
     sendButton.setToggleState(false, dontSendNotification);
     addAndMakeVisible(&sendButton);
     sendButton.addListener(this);
     
     nameLabel.setFont(Font(16));
     analysisTree.addListener(this);
     plotButton.setButtonText("Plot");
     plotButton.setToggleState(false, dontSendNotification);
     addAndMakeVisible(&plotButton);
     removeButton.setButtonText("x");
     addAndMakeVisible(&removeButton);
     plotButton.addListener(this);
     removeButton.addListener(this);
     refreshFromTree();
     */

}

/*==============================================================================
void SimpleAnalysisComponent::refreshFromTree()
{
    sendButton.setToggleState(analysisTree[AnalysisProperties::send],dontSendNotification);
    
    //plotButton.setToggleState(analysisTree[AnalysisProperties::plot], dontSendNotification);
    //customComponentRefreshFromTree();
    
    resized();
}
 */

//==============================================================================
void SimpleAnalysisComponent::resized()
{
    //removeButton.setBounds(0,0,20,20);
    //plotButton.setBounds(340, 0, 40, 20);
    
    activityIndicator.setBounds(30, yOffset, 80, 20);
    nameLabel.setBounds(120, yOffset, 200, 20);
    
    //sendButton.setBounds(280,0,40,20);
    //customComponentResized();
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

void SimpleAnalysisComponent::audioAnalysisChanged(AudioAnalysis* analysis)
{
    updateActivityIndicator();
}

void SimpleAnalysisComponent::updateActivityIndicator()
{
    if (analysis != nullptr)
    {
        if (analysis->send || analysis->getRelayed())
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

//==============================================================================
void SimpleAnalysisComponent::buttonClicked (Button* button)
{
    /*
    if (button == &sendButton)
    {
        bool state = sendButton.getToggleState();
        if (state == true)
        {
            //analysisTree.setProperty(AnalysisProperties::send, 0, nullptr);
        }
        else
        {
            //analysisTree.setProperty(AnalysisProperties::send, 1, nullptr);
        }
    }
    else if (button == &plotButton)
    {
        bool state = plotButton.getToggleState();
        if (state == true)
        {
            analysisTree.setProperty(AnalysisProperties::plot, 0, nullptr);
        }
        else
        {
            AnalysisModel::turnOffAllPlotting(analysisTree.getParent());
            analysisTree.setProperty(AnalysisProperties::plot, 1, nullptr);
        }
    }
    else if (button == &removeButton)
    {
        AnalysisModel::removeAnalysis(analysisTree);
    }
     */
}

/*==============================================================================
void SimpleAnalysisComponent::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (treeWhosePropertyHasChanged == analysisTree)
    {
        if (property == AnalysisProperties::send)
        {
            sendButton.setToggleState(analysisTree[AnalysisProperties::send],dontSendNotification);
        }
        else if (property == AnalysisProperties::plot)
        {
            plotButton.setToggleState(analysisTree[AnalysisProperties::plot], dontSendNotification);
        }
        customComponentPropertyChange(treeWhosePropertyHasChanged,property);
        resized();
    }
}
 */
