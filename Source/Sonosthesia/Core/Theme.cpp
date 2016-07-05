/*
  ==============================================================================

    Theme.cpp
    Created: 28 May 2016 6:40:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "Theme.h"


std::shared_ptr<Theme> Appearence::themeInstance = std::shared_ptr<Theme> (new SpaceTheme());

std::shared_ptr<Theme> Appearence::theme()
{
    return themeInstance;
}

void Appearence::setTheme(Name name)
{
    switch (name) {
            
        case Space:
            themeInstance = std::shared_ptr<Theme>( new SpaceTheme() );
            break;
            
        default:
            themeInstance = std::shared_ptr<Theme>( new SpaceTheme() );
            throw std::invalid_argument("unimplemented theme");
            break;
    }
}

SpaceTheme::SpaceTheme() :
    defaultFont(12, Font::FontStyleFlags::plain),
    boldFont(12, Font::FontStyleFlags::bold),
    titleFont(14, Font::FontStyleFlags::plain)
{
    
}

void SpaceTheme::label(Label& label, Level level)
{
    label.setColour(Label::ColourIds::textColourId, Colours::whitesmoke);
    label.setJustificationType(Justification::verticallyCentred | Justification::right);
}

void SpaceTheme::field(Label& label, Level level)
{
    label.setColour( Label::ColourIds::textColourId, Colours::darkgrey);
    label.setColour( Label::ColourIds::backgroundColourId, Colours::whitesmoke);
    label.setColour( Label::ColourIds::backgroundWhenEditingColourId, Colours::lightblue);
    label.setJustificationType(Justification::verticallyCentred | Justification::left);
}

void SpaceTheme::indicator(Label& label, Level level)
{
    switch (level) {
        
        case Theme::Primary:
            label.setColour( Label::ColourIds::textColourId, Colours::whitesmoke);
            label.setColour( Label::ColourIds::backgroundColourId, Colours::deepskyblue);
            break;
            
        case Theme::Warning:
            label.setColour( Label::ColourIds::textColourId, Colours::whitesmoke);
            label.setColour( Label::ColourIds::backgroundColourId, Colours::lightcoral);
            break;
            
        default:
            break;
    }
    
    label.setJustificationType(Justification::centred);
    
}

void SpaceTheme::textButton(TextButton& textButton, Level level)
{
    
}

void SpaceTheme::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level)
{
    
}

