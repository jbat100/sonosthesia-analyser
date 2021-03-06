/*
  ==============================================================================

    SettingsComponent.cpp
    Created: 14 Jul 2016 10:59:27am
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "SettingsComponent.h"
#include "ProcessorSettings.h"

#include "../Core/Theme.h"

//==============================================================================
SettingsComponent::SettingsComponent(SoundAnalyserAudioProcessor& _processor) : processor(_processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    //LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);
    
    pluginTitleLabel.setFont(logoFont);
    pluginTitleLabel.setText("Sound Analyser",dontSendNotification);
    addAndMakeVisible(&pluginTitleLabel);
    
    //String version = JucePlugin_VersionString;
    
    pluginVersionLabel.setFont(Font(10));
    pluginVersionLabel.setText(JucePlugin_VersionString , dontSendNotification);
    pluginVersionLabel.setColour(Label::ColourIds::textColourId, Colours::lightgrey);
    addAndMakeVisible(pluginVersionLabel);
    
    addAndMakeVisible(&bufferSizeComboBox);
    
    bufferSizeComboBox.addItem("64", 1);
    bufferSizeComboBox.addItem("128", 2);
    bufferSizeComboBox.addItem("256", 3);
    bufferSizeComboBox.addItem("512", 4);
    bufferSizeComboBox.addItem("1024", 5);
    bufferSizeComboBox.addItem("2048", 6);
    bufferSizeComboBox.addItem("4096", 7);
    
    bufferSizeValue.setEditable(true);
    bufferSizeValue.setText(String(ProcessorSettings::getInstance()->getBufferSize()), dontSendNotification);
    Appearence::theme()->field(bufferSizeValue);
    addAndMakeVisible(&bufferSizeValue);
    
    bufferSizeText.setText("Buffer Size: ", dontSendNotification);
    Appearence::theme()->label(bufferSizeText);
    addAndMakeVisible(&bufferSizeText);
    
    bufferSizeComboBox.addListener(this);
    bufferSizeValue.addListener(this);
    
    refresh();
    
}

SettingsComponent::~SettingsComponent()
{
}

void SettingsComponent::paint (Graphics& g)
{

}

void SettingsComponent::resized()
{
    bufferSizeText.setBounds(10, 10, 100, 20);
    // bufferSizeValue.setBounds(90,10,40,20);
    bufferSizeComboBox.setBounds(120, 10, 80, 20);
    
    float titleWidth = 280;
    pluginTitleLabel.setBounds(getWidth()-titleWidth-10, getHeight()-60, titleWidth, 50);
    pluginVersionLabel.setBounds(getWidth()-50, getHeight()-15, 40, 10);
    
}


//==============================================================================
void SettingsComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &bufferSizeValue)
    {
        ProcessorSettings::getInstance()->setBufferSize(bufferSizeValue.getTextValue().getValue());
    }
}

/*==============================================================================
void SettingsComponent::textEditorTextChanged (TextEditor& textEditor)
{
    processor.analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, textEditor.getText(), nullptr);
}
 */



//==============================================================================
void SettingsComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &bufferSizeComboBox)
    {
        int selectedItem = bufferSizeComboBox.getSelectedItemIndex();
        ProcessorSettings::getInstance()->setBufferSize( getBufferSizeFromIndex(selectedItem) );
    }
}

//==============================================================================
int SettingsComponent::getBufferSizeFromIndex(int index)
{
    int minBufferSize = 64;
    return minBufferSize * powl(2, index);
}

//==============================================================================
int SettingsComponent::getIndexFromBufferSize(int bufferSize)
{
    switch(bufferSize) {
        case 64:
           return BufferSize64;
        case 128:
            return BufferSize128;
        case 256:
            return BufferSize256;
        case 512:
            return BufferSize512;
        case 1024:
            return BufferSize1024;
        case 2048:
            return BufferSize2048;
        case 4096:
            return BufferSize4096;
        default:
            return BufferSize64;
    }
}

void SettingsComponent::buttonClicked (Button* button)
{

}

void SettingsComponent::refresh()
{
    int bufferSize = ProcessorSettings::getInstance()->getBufferSize();
    bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(bufferSize));
}


