/*
 ==============================================================================
 This file was auto-generated!
 It contains the basic framework code for a JUCE plugin editor.
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SplitsiesAudioProcessorEditor::SplitsiesAudioProcessorEditor (SplitsiesAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    
    // Setting up GUI
    
    setSize (200, 400);
    
    // First filter
    
    filterMenu.setJustificationType(Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("Band Pass", 2);
    filterMenu.addItem("High Pass", 3);
    addAndMakeVisible(&filterMenu);
    
    filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial.setRange(20.0f, 20000.0f);
    filterCutoffDial.setValue(600.0f);
    filterCutoffDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoffDial);
    
    filterResDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterResDial.setRange(1.0f, 5.0f);
    filterResDial.setValue(2.0f);
    filterResDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResDial);
    
    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "cutoff", filterCutoffDial);
    
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "resonance", filterResDial);
    
    filterMenuChoice = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterMenu", filterMenu);
    
    filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);
    
 // Second filter
    
    filterMenu02.setJustificationType(Justification::centred);
    filterMenu02.addItem("Low Pass", 1);
    filterMenu02.addItem("Band Pass", 2);
    filterMenu02.addItem("High Pass", 3);
    addAndMakeVisible(&filterMenu02);
    
    filterCutoffDial02.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial02.setRange(20.0f, 20000.0f);
    filterCutoffDial02.setValue(600.0f);
    filterCutoffDial02.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDial02.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoffDial02);
    
    filterResDial02.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterResDial02.setRange(1.0f, 5.0f);
    filterResDial02.setValue(2.0f);
    filterResDial02.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResDial02.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResDial02);
    
    filterCutoffValue02 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "cutoff02", filterCutoffDial02);
    
    filterResValue02 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "resonance02", filterResDial02);
    
    filterMenuChoice02 = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterMenu02", filterMenu02);
    
    filterCutoffDial02.setSkewFactorFromMidPoint(1000.0f);
    
    
    
}

SplitsiesAudioProcessorEditor::~SplitsiesAudioProcessorEditor()
{
}

//==============================================================================
void SplitsiesAudioProcessorEditor::paint (Graphics& g)
{
    
    // Background UI
    
    Rectangle<int> titleArea (0, 20, getWidth(), 20);
    Rectangle<int> titleArea02 (0, 200, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::turquoise);
    
    // Labels
    
    g.drawText("First Filter Type", titleArea, Justification::centredTop);
    g.drawText("Cutoff", 46, 71, 50, 25, Justification::centredLeft);
    g.drawText("Resonance", 104, 70, 70, 25, Justification::centredLeft);
    
    g.drawText("Second Filter Type", titleArea02, Justification::centredTop);
    g.drawText("Cutoff", 46, 261, 50, 25, Justification::centredLeft);
    g.drawText("Resonance", 104, 260, 70, 25, Justification::centredLeft);
    
    
    // Border
    
    Rectangle <float> area (15, 10, 170, 360);
    
    g.setColour(Colours::teal);
    g.drawRoundedRectangle(area, 20.0f, 3.0f);
}

void SplitsiesAudioProcessorEditor::resized()
{
    
    // Menus

    Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoffDial.setBounds (30, 90, 70, 70);
    filterResDial.setBounds (100, 90, 70, 70);
    
    filterMenu02.setBounds(40, 220, 119, 19);
    filterCutoffDial02.setBounds (30, 280, 70, 70);
    filterResDial02.setBounds (100, 280, 70, 70);
}
