/*
  ==============================================================================

    OriginalRootComponent.cpp
    Created: 3 Jul 2016 4:45:05pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../Audio Analysis/AnalysisModel.h"
#include "../PluginProcessor.h"

#include "OriginalRootComponent.h"
#include "SimpleAnalysisComponent.h"
#include "AnalysisSelectionComponent.h"

/*
 
 //==============================================================================
 void SoundAnalyserAudioProcessorEditor::setValueTree(ValueTree tree)
 {
 analyserTree.removeListener(this);
 
 analyserTree = tree;
 
 analyserTree.addListener(this);
 
 refreshFromTree();
 }
 
 */

//==============================================================================
OriginalRootComponent::OriginalRootComponent() : processor(nullptr)
{
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);
    
    //MemoryInputStream mis(BinaryData::TenorSansRegular_ttf, BinaryData::TenorSansRegular_ttfSize, false);
    //Typeface::Ptr typeface = new CustomTypeface(mis);
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);
    
    newAnalysisButton.setButtonText("+");
    addAndMakeVisible(&newAnalysisButton);
    newAnalysisButton.addListener(this);
    
    OSCPort.setColour(Label::ColourIds::textColourId, Colours::black);
    OSCPort.setText(processor->analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    OSCPort.setEditable(true);
    OSCPort.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    OSCPort.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&OSCPort);
    
    IPAddressValue.setColour(Label::ColourIds::textColourId, Colours::black);
    IPAddressValue.setText(processor->analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    IPAddressValue.setEditable(true);
    IPAddressValue.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    IPAddressValue.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&IPAddressValue);
    
    analyserId.setColour(Label::ColourIds::textColourId, Colours::black);
    analyserId.setText(processor->analyserTree[AnalysisModel::Ids::AnalyserId], dontSendNotification);
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
    bufferSizeValue.setText(processor->analyserTree[AnalysisModel::Ids::BufferSize].toString(), dontSendNotification);
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
    processor->analyserTree.addListener(this);
    
    analyserId.addListener(this);
    
    OSCPort.addListener(this);
    IPAddressValue.addListener(this);
    bufferSizeValue.addListener(this);
    
    refreshFromTree();
    
}

//==============================================================================
OriginalRootComponent::OriginalRootComponent(SoundAnalyserAudioProcessor* _processor) :
    processor(_processor)
{
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);
    
    //MemoryInputStream mis(BinaryData::TenorSansRegular_ttf, BinaryData::TenorSansRegular_ttfSize, false);
    //Typeface::Ptr typeface = new CustomTypeface(mis);
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);
    
    newAnalysisButton.setButtonText("+");
    addAndMakeVisible(&newAnalysisButton);
    newAnalysisButton.addListener(this);
    
    OSCPort.setColour(Label::ColourIds::textColourId, Colours::black);
    OSCPort.setText(processor->analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    OSCPort.setEditable(true);
    OSCPort.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    OSCPort.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&OSCPort);
    
    IPAddressValue.setColour(Label::ColourIds::textColourId, Colours::black);
    IPAddressValue.setText(processor->analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    IPAddressValue.setEditable(true);
    IPAddressValue.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    IPAddressValue.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&IPAddressValue);
    
    analyserId.setColour(Label::ColourIds::textColourId, Colours::black);
    analyserId.setText(processor->analyserTree[AnalysisModel::Ids::AnalyserId], dontSendNotification);
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
    bufferSizeValue.setText(processor->analyserTree[AnalysisModel::Ids::BufferSize].toString(), dontSendNotification);
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
    processor->analyserTree.addListener(this);
    
    analyserId.addListener(this);
    
    OSCPort.addListener(this);
    IPAddressValue.addListener(this);
    bufferSizeValue.addListener(this);
    
    refreshFromTree();
        
}

OriginalRootComponent::~OriginalRootComponent()
{
}

void OriginalRootComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void OriginalRootComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    bufferSizeText.setBounds(10, 10, 70, 20);
    // bufferSizeValue.setBounds(90,10,40,20);
    bufferSizeComboBox.setBounds(80, 10, 60, 20);
    
    int lastComponentY = 0;
    
    for (int i = 0;i < analysisComponents.size();i++)
    {
        analysisComponents[i]->setBounds(10, 60+lastComponentY, analysisComponents[i]->getWidth(), analysisComponents[i]->getHeight());
        lastComponentY += analysisComponents[i]->getHeight();
    }
    
    newAnalysisButton.setBounds(10, getHeight()-60, 50, 50);
    
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

//==============================================================================
void OriginalRootComponent::refreshFromTree()
{
    analysisComponents.clear();
    
    for (int i = 0;i < processor->analyserTree.getNumChildren();i++)
    {
        ValueTree analysisTree = processor->analyserTree.getChild(i);
        addAnalysis(analysisTree);
    }
    
    analyserId.setText(processor->analyserTree[AnalysisModel::Ids::AnalyserId],dontSendNotification);
    
    OSCPort.setText(processor->analyserTree[AnalysisModel::Ids::Port],dontSendNotification);
    IPAddressValue.setText(processor->analyserTree[AnalysisModel::Ids::IPAddress],dontSendNotification);
    
    
    int currentBufferSize = processor->analyserTree[AnalysisModel::Ids::BufferSize];
    
    bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(currentBufferSize));
    
    
    resized();
}


//==============================================================================
void OriginalRootComponent::buttonClicked (Button* button)
{
    if (button == &newAnalysisButton)
    {
        AlertWindow w ("Add new analysis..",
                       "Please slect a new device from the list below",
                       AlertWindow::NoIcon);
        
        ScopedPointer<AnalysisSelectionComponent> analysisSelector;
        
        analysisSelector = new AnalysisSelectionComponent(processor->analyserTree, &processor->analyser);
        
        w.addCustomComponent(analysisSelector);
        
        w.addButton ("ok",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        w.setColour(AlertWindow::ColourIds::backgroundColourId, Colours::lightgrey);
        
        
        if (w.runModalLoop() != 0) // if they picked 'ok'
        {
            const int optionIndexChosen = analysisSelector->getSelectedAnalysis();
            
            if (optionIndexChosen >= 0)
            {
                AudioAnalysis *chosenAnalysis = processor->analyser.audioAnalyses[optionIndexChosen];
                AnalysisModel::addNewAnalysis(processor->analyserTree, chosenAnalysis->createAnalysisTree());
            }
        }
        
    }
}

//==============================================================================
void OriginalRootComponent::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &analyserId)
    {
        processor->analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, analyserId.getText(), nullptr);
    }
    else if (labelThatHasChanged == &OSCPort)
    {
        processor->analyserTree.setProperty(AnalysisModel::Ids::Port, OSCPort.getText(),nullptr);
    }
    else if (labelThatHasChanged == &IPAddressValue)
    {
        processor->analyserTree.setProperty(AnalysisModel::Ids::IPAddress, IPAddressValue.getText(),nullptr);
    }
    else if (labelThatHasChanged == &bufferSizeValue)
    {
        AnalysisModel::setBufferSize(processor->analyserTree, bufferSizeValue.getTextValue().getValue());
    }
}

//==============================================================================
void OriginalRootComponent::textEditorTextChanged (TextEditor& textEditor)
{
    
    processor->analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, textEditor.getText(), nullptr);
    
}

//==============================================================================
void OriginalRootComponent::addAnalysis(ValueTree& analysisTree)
{
    
    for (int i = 0;i < processor->analyser.audioAnalyses.size();i++)
    {
        if (analysisTree.getType() == processor->analyser.audioAnalyses[i]->getIdentifier())
        {
            analysisComponents.add(processor->analyser.audioAnalyses[i]->getGUIComponent(analysisTree));
            
        }
    }
    
    
    addChildComponent(analysisComponents.getLast());
    analysisComponents.getLast()->setVisible(true);
    
    resized();
}

//==============================================================================
void OriginalRootComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &bufferSizeComboBox)
    {
        int selectedItem = bufferSizeComboBox.getSelectedItemIndex();
        AnalysisModel::setBufferSize(processor->analyserTree, getBufferSizeFromIndex(selectedItem));
    }
}

//==============================================================================
int OriginalRootComponent::getBufferSizeFromIndex(int index)
{
    int minBufferSize = 64;
    return minBufferSize * powl(2,index);
}

//==============================================================================
int OriginalRootComponent::getIndexFromBufferSize(int bufferSize)
{
    if (bufferSize == 64)
    {
        return BufferSize64;
    }
    else if (bufferSize == 128)
    {
        return BufferSize128;
    }
    else if (bufferSize == 256)
    {
        return BufferSize256;
    }
    else if (bufferSize == 512)
    {
        return BufferSize512;
    }
    else if (bufferSize == 1024)
    {
        return BufferSize1024;
    }
    else if (bufferSize == 2048)
    {
        return BufferSize2048;
    }
    else if (bufferSize == 4096)
    {
        return BufferSize4096;
    }
    else
    {
        return BufferSize64;
    }
}

//==============================================================================
void OriginalRootComponent::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
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
        int newBufferSize = processor->analyserTree[property];
        bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(newBufferSize));
    }
}

//==============================================================================
void OriginalRootComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    addAnalysis(childWhichHasBeenAdded);
}

//==============================================================================
void OriginalRootComponent::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
{
    refreshFromTree();
}

//==============================================================================
void OriginalRootComponent::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) {}

//==============================================================================
void OriginalRootComponent::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) {}

