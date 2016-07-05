/*
  ==============================================================================

    Utils.cpp
    Created: 16 May 2016 5:01:21pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include <stdexcept>

#include "Utils.h"

// we start the counter at 1 as juce item ids generally don't like 0
NumericIdentifierGenerator::NumericIdentifierGenerator() : counter(1) {}

int NumericIdentifierGenerator::getNumericIdentifier(String identifier)
{
    auto i = identifiers.find(identifier);
    
    if (i == identifiers.end())
    {
        identifiers[identifier] = counter;
        counter++;
        return identifiers[identifier];
    }
    
    return i->second;
}

String NumericIdentifierGenerator::getStringIdentifier(int identifier)
{
    for (auto i = identifiers.begin(); i != identifiers.end(); i++)
    {
        if (i->second == identifier) return i->first;
    }
    
    throw std::invalid_argument( "unknown identifier" );
}

