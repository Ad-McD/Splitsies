/*
 ==============================================================================
 This file was auto-generated!
 It contains the basic framework code for a JUCE plugin processor.
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SplitsiesAudioProcessor::SplitsiesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ), tree(*this, nullptr)
#endif
{
    
    //Setting up the ranges and parameters of both filters
    
    NormalisableRange<float> cutoffRange (20.0f, 20000.0f);
    NormalisableRange<float> resRange (1.0f, 5.0f);
    NormalisableRange<float> filterMenuRange (0, 2);
    
    NormalisableRange<float> cutoffRange02 (20.0f, 20000.0f);
    NormalisableRange<float> resRange02 (1.0f, 5.0f);
    NormalisableRange<float> filterMenuRange02 (0, 2);
    
    tree.createAndAddParameter("cutoff", "Cutoff", "cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("resonance", "Resonance", "resonance", resRange, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("filterMenu", "FilterMenu", "filterMenu", filterMenuRange, 0, nullptr, nullptr);
    
    tree.createAndAddParameter("cutoff02", "Cutoff02", "cutoff02", cutoffRange02, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("resonance02", "Resonance02", "resonance02", resRange02, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("filterMenu02", "FilterMenu02", "filterMenu02", filterMenuRange02, 0, nullptr, nullptr);
}

SplitsiesAudioProcessor::~SplitsiesAudioProcessor()
{
}

//==============================================================================
const String SplitsiesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SplitsiesAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SplitsiesAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SplitsiesAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SplitsiesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SplitsiesAudioProcessor::getNumPrograms()
{
    return 2;   // Some hosts don't like this set to 0 programs,
    // Set so to at least 1, even if you're not really implementing programs.
}

int SplitsiesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SplitsiesAudioProcessor::setCurrentProgram (int index)
{
}

const String SplitsiesAudioProcessor::getProgramName (int index)
{
    return {};
}

void SplitsiesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SplitsiesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getMainBusNumOutputChannels();

    // Prepare the filters
    
    stateVariableFilter.reset();
    stateVariableFilter02.reset();
    updateFilter();
    updateFilter02();
    stateVariableFilter.prepare(spec);
    stateVariableFilter02.prepare(spec);
}

void SplitsiesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void SplitsiesAudioProcessor::updateFilter()
{
    
    // Setup the Pass types of the first State Varible Filter
    
    int menuChoice = *tree.getRawParameterValue("filterMenu");
    int cutoff = *tree.getRawParameterValue("cutoff");
    int res = *tree.getRawParameterValue("resonance");
    
    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        
        stateVariableFilter.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        
        stateVariableFilter.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        
        stateVariableFilter.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    
    
}

void SplitsiesAudioProcessor::updateFilter02()
{
    
    // Set up the Pass types of the second State Variable Filter
    
    int menuChoice = *tree.getRawParameterValue("filterMenu02");
    int cutoff = *tree.getRawParameterValue("cutoff02");
    int res = *tree.getRawParameterValue("resonance02");
    
    if (menuChoice == 0)
    {
        stateVariableFilter02.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        
        stateVariableFilter02.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    if (menuChoice == 1)
    {
        stateVariableFilter02.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        
        stateVariableFilter02.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    if (menuChoice == 2)
    {
        stateVariableFilter02.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        
        stateVariableFilter02.state->setCutOffFrequency (lastSampleRate, cutoff, res);
    }
    
    
    
}




#ifndef JucePlugin_PreferredChannelConfigurations
bool SplitsiesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
    
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void SplitsiesAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
// Attempt ** at duplicating input audio to send to different filters for separate processing
    
    AudioSampleBuffer dup_buffer(buffer);
    
    dsp::AudioBlock<float> block (buffer);
    dsp::AudioBlock<float> block02 (dup_buffer);
    
// ** Still feeds audio through filters in series, where the second affects the output of the first
    

    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
    stateVariableFilter02.process(dsp::ProcessContextReplacing<float> (block02));
    
        updateFilter();
        updateFilter02();
    
}

//==============================================================================
bool SplitsiesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SplitsiesAudioProcessor::createEditor()
{
    return new SplitsiesAudioProcessorEditor (*this);
}

//==============================================================================
void SplitsiesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SplitsiesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SplitsiesAudioProcessor();
}
