/*
  ==============================================================================

    SettingsComponent.cpp
    Created: 14 Jul 2016 10:59:27am
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "SettingsComponent.h"

//==============================================================================
SettingsComponent::SettingsComponent(SoundAnalyserAudioProcessor& _processor) : processor(_processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);
    
    OSCPort.setColour(Label::ColourIds::textColourId, Colours::black);
    OSCPort.setText(processor.analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    OSCPort.setEditable(true);
    OSCPort.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    OSCPort.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&OSCPort);
    
    IPAddressValue.setColour(Label::ColourIds::textColourId, Colours::black);
    IPAddressValue.setText(processor.analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    IPAddressValue.setEditable(true);
    IPAddressValue.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    IPAddressValue.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&IPAddressValue);
    
    analyserId.setColour(Label::ColourIds::textColourId, Colours::black);
    analyserId.setText(processor.analyserTree[AnalysisModel::Ids::AnalyserId], dontSendNotification);
    analyserId.setEditable(true);
    analyserId.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    analyserId.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&analyserId);
    
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
    bufferSizeValue.setText(processor.analyserTree[AnalysisModel::Ids::BufferSize].toString(), dontSendNotification);
    bufferSizeValue.setColour(Label::ColourIds::textColourId, Colours::black);
    bufferSizeValue.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    bufferSizeValue.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&bufferSizeValue);
    
    bufferSizeText.setText("Buffer Size: ", dontSendNotification);
    addAndMakeVisible(&bufferSizeText);
    
    IPAddressText.setText("IP Address:", dontSendNotification);
    addAndMakeVisible(&IPAddressText);
    
    OSCPortText.setText("Port:", dontSendNotification);
    addAndMakeVisible(&OSCPortText);
    
    analyserIdText.setText("Analyser Id:", dontSendNotification);
    addAndMakeVisible(&analyserIdText);
    
    bufferSizeComboBox.addListener(this);
    processor.analyserTree.addListener(this);
    
    analyserId.addListener(this);
    
    OSCPort.addListener(this);
    IPAddressValue.addListener(this);
    bufferSizeValue.addListener(this);
    
}

SettingsComponent::~SettingsComponent()
{
}

void SettingsComponent::paint (Graphics& g)
{

}

void SettingsComponent::resized()
{
    bufferSizeText.setBounds(10, 10, 70, 20);
    // bufferSizeValue.setBounds(90,10,40,20);
    bufferSizeComboBox.setBounds(80, 10, 60, 20);
    
    IPAddressText.setBounds(getWidth()-450, 10, 80, 20);
    IPAddressValue.setBounds(getWidth()-360, 10, 90, 20);
    
    OSCPortText.setBounds(getWidth()-260, 10, 40, 20);
    OSCPort.setBounds(getWidth()-210, 10, 40, 20);
    
    analyserIdText.setBounds(getWidth()-170, 10, 80, 20);
    analyserId.setBounds(getWidth()-80, 10, 70, 20);
    
    float titleWidth = 280;
    pluginTitleLabel.setBounds(getWidth()-titleWidth-10, getHeight()-60, titleWidth, 50);
    
    pluginVersionLabel.setBounds(getWidth()-50, getHeight()-15, 40, 10);
    
}

void SettingsComponent::refreshFromTree()
{
    analyserId.setText(processor.analyserTree[AnalysisModel::Ids::AnalyserId], dontSendNotification);
    
    OSCPort.setText(processor.analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    IPAddressValue.setText(processor.analyserTree[AnalysisModel::Ids::IPAddress], dontSendNotification);
    
    int currentBufferSize = processor.analyserTree[AnalysisModel::Ids::BufferSize];
    
    bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(currentBufferSize));
    
    resized();
}

//==============================================================================
void SettingsComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &analyserId)
    {
        processor.analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, analyserId.getText(), nullptr);
    }
    else if (labelThatHasChanged == &OSCPort)
    {
        processor.analyserTree.setProperty(AnalysisModel::Ids::Port, OSCPort.getText(),nullptr);
    }
    else if (labelThatHasChanged == &IPAddressValue)
    {
        processor.analyserTree.setProperty(AnalysisModel::Ids::IPAddress, IPAddressValue.getText(),nullptr);
    }
    else if (labelThatHasChanged == &bufferSizeValue)
    {
        AnalysisModel::setBufferSize(processor.analyserTree, bufferSizeValue.getTextValue().getValue());
    }
}

//==============================================================================
void SettingsComponent::textEditorTextChanged (TextEditor& textEditor)
{
    processor.analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, textEditor.getText(), nullptr);
}



//==============================================================================
void SettingsComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &bufferSizeComboBox)
    {
        int selectedItem = bufferSizeComboBox.getSelectedItemIndex();
        AnalysisModel::setBufferSize(processor.analyserTree, getBufferSizeFromIndex(selectedItem));
    }
}

//==============================================================================
int SettingsComponent::getBufferSizeFromIndex(int index)
{
    int minBufferSize = 64;
    return minBufferSize * powl(2,index);
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

//==============================================================================

void SettingsComponent::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    if (property == AnalysisModel::Ids::AnalyserId)
    {
        refreshFromTree();
    }
    else if (property == AnalysisModel::Ids::IPAddress)
    {
        refreshFromTree();
    }
    else if (property == AnalysisModel::Ids::Port)
    {
        refreshFromTree();
    }
    else if (property == AnalysisModel::Ids::BufferSize)
    {
        int newBufferSize = processor.analyserTree[property];
        bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(newBufferSize));
    }
}

void SettingsComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    //addAnalysis(childWhichHasBeenAdded);
}

void SettingsComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
{
    refreshFromTree();
}

void SettingsComponent::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{

}

void SettingsComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{

}
