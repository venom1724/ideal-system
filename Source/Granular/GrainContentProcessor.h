#pragma once
#include <vector>
#include "Grain.h"
#include "GrainTable.h"

typedef std::vector<Grain> GrainVector;

class GrainContentProcessor : public AudioProcessorValueTreeState::Listener
{
	AudioProcessorValueTreeState& m_parameters;

	float m_sampleRate;
	GrainVector m_childGrains;
	int m_samplesPerSpawn, m_samplesUntilSpawn;

	GrainTable m_hannTable, m_triwTable, m_sineTable, m_audioTable;

	bool m_running;
	float m_phasorSpeed;

	Phasor m_playbackPhasor;

	float* m_grainSizeMultiplier = nullptr;
	float* m_startPosition = nullptr;
	float* m_blendAmount = nullptr;

	float m_masterPitch;

	float* m_bpm = nullptr;
	float* m_division = nullptr;
	
	float m_pitchOffset;

public:
	GrainContentProcessor(AudioProcessorValueTreeState& parameters, float sampleRate = 44100.0f);
	void setSampleRate(float samplerate);

	void process(float* leftChannel, float* rightChannel, int blockSize, AudioPlayHead* playhead);

	void setPlayState(bool state);

	void setAudioSize(int size);
	void setAudioSample(int index, float value);
	void calculatePhasorSpeed();

	void setPitch(float pitch);

	void calculateSamplesPerStep();
	void setBPM(float bpm);
	void setDivision(float div);

	void setGrainPitch(float midiValue);

	int getBufferSize();
	void fillBuffer(float* buf);

	void parameterChanged(const String& parameterID, float newValue) override;

};