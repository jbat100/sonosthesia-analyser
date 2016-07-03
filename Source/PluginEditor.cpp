//=======================================================================
/** @file PluginEditor.cpp
 *  @brief The top level GUI class for the Sound Analyser
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
//======================================================================

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/BinaryData.h"


//==============================================================================
SoundAnalyserAudioProcessorEditor::SoundAnalyserAudioProcessorEditor (SoundAnalyserAudioProcessor* ownerFilter,  ValueTree analyserTree_)
    : AudioProcessorEditor (ownerFilter), analyserTree(analyserTree_)
{
    // This is where our plugin's editor size is set.
    setSize (600, 500);
    
    LookAndFeel::setDefaultLookAndFeel(&pluginLookAndFeel);
    
    //MemoryInputStream mis(BinaryData::TenorSansRegular_ttf, BinaryData::TenorSansRegular_ttfSize, false);
    //Typeface::Ptr typeface = new CustomTypeface(mis);
    
    Font logoFont;//(typeface);
    logoFont.setHeight(40);

    

    
    newAnalysisButton.setButtonText("+");
    addAndMakeVisible(&newAnalysisButton);
    newAnalysisButton.addListener(this);
    
    OSCPort.setColour(Label::ColourIds::textColourId, Colours::black);
    OSCPort.setText(analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    OSCPort.setEditable(true);
    OSCPort.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    OSCPort.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&OSCPort);
    
    IPAddressValue.setColour(Label::ColourIds::textColourId, Colours::black);
    IPAddressValue.setText(analyserTree[AnalysisModel::Ids::Port], dontSendNotification);
    IPAddressValue.setEditable(true);
    IPAddressValue.setColour(Label::ColourIds::backgroundColourId, Colours::white);
    IPAddressValue.setColour(Label::ColourIds::outlineColourId, Colours::lightgrey);
    addAndMakeVisible(&IPAddressValue);
    
    analyserId.setColour(Label::ColourIds::textColourId, Colours::black);
    analyserId.setText(analyserTree[AnalysisModel::Ids::AnalyserId], dontSendNotification);
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
    bufferSizeValue.setText(analyserTree[AnalysisModel::Ids::BufferSize].toString(), dontSendNotification);
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
    
    
    plotHeight = 150;
    plotY = 40;
    

    bufferSizeComboBox.addListener(this);
    analyserTree.addListener(this);
    
    analyserId.addListener(this);

    OSCPort.addListener(this);
    IPAddressValue.addListener(this);
    bufferSizeValue.addListener(this);
    
    refreshFromTree();
    
    startTimer (50);
}



//==============================================================================
SoundAnalyserAudioProcessorEditor::~SoundAnalyserAudioProcessorEditor()
{
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::setValueTree(ValueTree tree)
{
    analyserTree.removeListener(this);
    
    analyserTree = tree;
    
    analyserTree.addListener(this);
    
    refreshFromTree();
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::refreshFromTree()
{
    analysisComponents.clear();
    
    for (int i = 0;i < analyserTree.getNumChildren();i++)
    {
        ValueTree analysisTree = analyserTree.getChild(i);
        
        addAnalysis(analysisTree);
    }
    
    analyserId.setText(analyserTree[AnalysisModel::Ids::AnalyserId],dontSendNotification);
    
    OSCPort.setText(analyserTree[AnalysisModel::Ids::Port],dontSendNotification);
    IPAddressValue.setText(analyserTree[AnalysisModel::Ids::IPAddress],dontSendNotification);
    
    
    int currentBufferSize = analyserTree[AnalysisModel::Ids::BufferSize];
    
    bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(currentBufferSize));

    
    resized();
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::paint (Graphics& g)
{
    PluginLookAndFeel::fillWithBackgroundTexture (g);
    g.setColour (Colour::fromRGBA(56, 61, 68,245));
    g.fillAll (Colour::fromRGBA(34, 34, 34,245));
    
    if (getProcessor()->analyser.currentAnalysisToPlotType == FloatOutput)
    {
        int N = getProcessor()->analyser.plotHistory.size();
        
        int plotX = (getWidth()- N)/2;
        
        
        g.fillRect(plotX, plotY, N, plotHeight);
        
        g.setColour(Colours::lightsteelblue);

        float previousValue = getProcessor()->analyser.plotHistory[0];
        
        // get the max value
        float maxValue = -10000;
        for (int i = 0;i < N;i++)
        {
            if (getProcessor()->analyser.plotHistory[i] > maxValue)
            {
                maxValue = getProcessor()->analyser.plotHistory[i];
            }
        }
        
        // do the plotting
        for (int i = 0;i < N-1;i++)
        {
            float currentValue = getProcessor()->analyser.plotHistory[i+1];
            
            int p1 = plotY + (plotHeight - ((previousValue/maxValue)*plotHeight));
            int p2 = plotY + (plotHeight - ((currentValue/maxValue)*plotHeight));
            
            g.setColour(Colours::lightsteelblue);
            g.drawLine(plotX+i,p1,plotX+i+1,p2);
            
            previousValue = currentValue;
        }
    
    }
    else if (getProcessor()->analyser.currentAnalysisToPlotType == VectorOutput)
    {
        int N = getProcessor()->analyser.vectorPlot.size();
        int plotWidth = 512;
        
        int plotX = (getWidth() - plotWidth) / 2;
        
        g.fillRect(plotX,plotY, plotWidth,plotHeight);
        
        g.setColour(Colours::greenyellow);
        
        float previousValue = getProcessor()->analyser.vectorPlot[0];
        
        // get the max value
        float maxValue = -10000;
        for (int i = 0;i < N;i++)
        {
            if (getProcessor()->analyser.vectorPlot[i] > maxValue)
            {
                maxValue = getProcessor()->analyser.vectorPlot[i];
            }
        }
        
        // do the plotting
        for (int i = 0;i < N-1;i++)
        {
            float currentValue = getProcessor()->analyser.vectorPlot[i+1];
            
            int p1 = plotY + (plotHeight - ((previousValue/maxValue)*plotHeight));
            int p2 = plotY + (plotHeight - ((currentValue/maxValue)*plotHeight));
            
            int x1 = i*round(512.0/((double)N-1.));
            int x2 = (i+1)*round(512.0/((double)N-1.));
            
            g.drawLine(plotX+x1,p1,plotX+x2,p2);

            previousValue = currentValue;
        }
        
    }
    
    
    //g.setFont (15.0f);
    //g.drawFittedText (String(previousValue), 0, 0, getWidth(), getHeight(), Justification::centred, 1);

   // g.drawLine(10, 10, getWidth()-10, getHeight()-10);
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::resized()
{
    bufferSizeText.setBounds(10, 10, 70, 20);
   // bufferSizeValue.setBounds(90,10,40,20);
    bufferSizeComboBox.setBounds(80, 10, 60, 20);
    
    int lastComponentY = 0;
    
    for (int i = 0;i < analysisComponents.size();i++)
    {
        analysisComponents[i]->setBounds(10,(plotY+plotHeight+25)+lastComponentY,analysisComponents[i]->getWidth(),analysisComponents[i]->getHeight());
        
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
SoundAnalyserAudioProcessor* SoundAnalyserAudioProcessorEditor::getProcessor() const
{
    return static_cast <SoundAnalyserAudioProcessor*> (getAudioProcessor());
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::timerCallback()
{
    repaint();
}


//==============================================================================
void SoundAnalyserAudioProcessorEditor::buttonClicked (Button* button)
{    
    if (button == &newAnalysisButton)
    {
        AlertWindow w ("Add new analysis..",
                       "Please slect a new device from the list below",
                       AlertWindow::NoIcon);
                
        ScopedPointer<AnalysisSelectionComponent> analysisSelector;
        
        analysisSelector = new AnalysisSelectionComponent(analyserTree,&getProcessor()->analyser);
        
        w.addCustomComponent(analysisSelector);
        
        w.addButton ("ok",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        w.setColour(AlertWindow::ColourIds::backgroundColourId, Colours::lightgrey);
        
    
        if (w.runModalLoop() != 0) // if they picked 'ok'
        {
            const int optionIndexChosen = analysisSelector->getSelectedAnalysis();
            
            if (optionIndexChosen >= 0)
            {
                AudioAnalysis *chosenAnalysis = getProcessor()->analyser.audioAnalyses[optionIndexChosen];
                
                AnalysisModel::addNewAnalysis(analyserTree, chosenAnalysis->createAnalysisTree());
            }
        }
         
    }
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::labelTextChanged (Label* labelThatHasChanged)
{
    if (labelThatHasChanged == &analyserId)
    {
        analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, analyserId.getText(), nullptr);
    }
    else if (labelThatHasChanged == &OSCPort)
    {
        analyserTree.setProperty(AnalysisModel::Ids::Port, OSCPort.getText(),nullptr);
    }
    else if (labelThatHasChanged == &IPAddressValue)
    {
        analyserTree.setProperty(AnalysisModel::Ids::IPAddress, IPAddressValue.getText(),nullptr);
    }
    else if (labelThatHasChanged == &bufferSizeValue)
    {
        AnalysisModel::setBufferSize(analyserTree,bufferSizeValue.getTextValue().getValue());
    }
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::textEditorTextChanged (TextEditor& textEditor)
{
    
    analyserTree.setProperty(AnalysisModel::Ids::AnalyserId, textEditor.getText(), nullptr);
    
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::addAnalysis(ValueTree& analysisTree)
{

    for (int i = 0;i < getProcessor()->analyser.audioAnalyses.size();i++)
    {
        if (analysisTree.getType() == getProcessor()->analyser.audioAnalyses[i]->getIdentifier())
        {
            analysisComponents.add(getProcessor()->analyser.audioAnalyses[i]->getGUIComponent(analysisTree));

        }
    }
    
    
    addChildComponent(analysisComponents.getLast());
    analysisComponents.getLast()->setVisible(true);
    
    resized();
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &bufferSizeComboBox)
    {
        int selectedItem = bufferSizeComboBox.getSelectedItemIndex();
        
        AnalysisModel::setBufferSize(analyserTree,getBufferSizeFromIndex(selectedItem));
    }
}

//==============================================================================
int SoundAnalyserAudioProcessorEditor::getBufferSizeFromIndex(int index)
{
    int minBufferSize = 64;
    
    return minBufferSize * powl(2,index);
}

//==============================================================================
int SoundAnalyserAudioProcessorEditor::getIndexFromBufferSize(int bufferSize)
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
void SoundAnalyserAudioProcessorEditor::valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
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
        int newBufferSize = analyserTree[property];
        
        bufferSizeComboBox.setSelectedItemIndex(getIndexFromBufferSize(newBufferSize));
    }
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
    addAnalysis(childWhichHasBeenAdded);
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)

{
    refreshFromTree();
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    
}

//==============================================================================
void SoundAnalyserAudioProcessorEditor::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
    
}
