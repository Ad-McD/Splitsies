/*
 ==============================================================================
 This file was auto-generated!
 It contains the basic framework code for a JUCE plugin editor.
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
 */
class SplitsiesAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SplitsiesAudioProcessorEditor (SplitsiesAudioProcessor&);
    ~SplitsiesAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment>
    filterMenuChoice;
    
    //Filter02
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue02;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue02;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment>
    filterMenuChoice02;
    
    
private:
    Slider filterCutoffDial;
    Slider filterResDial;
    ComboBox filterMenu;
    
    //Filter02
    
    Slider filterCutoffDial02;
    Slider filterResDial02;
    ComboBox filterMenu02;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SplitsiesAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitsiesAudioProcessorEditor)
};
