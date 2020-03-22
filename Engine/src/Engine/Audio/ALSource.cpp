#include "ALSource.h"
#include <AL/al.h>

namespace Engine
{
	ALSource::ALSource()
	{
		alGenSources(1, &m_data.sourceID);
	}

	ALSource::~ALSource()
	{
		alDeleteSources(1, &m_data.sourceID);
		ENGINE_WARN("Destroyed OpenAL source.");
	}

	void ALSource::SetBuffer(const std::string& filename, const std::string& bufferKey, const Ref<AudioMaster>& audioMaster)
	{
		audioMaster->LoadSound(filename, bufferKey);
		alSourcei(m_data.sourceID, AL_BUFFER, audioMaster->GetBuffer(bufferKey)->GetBuffer());
		ENGINE_ASSERT((alGetError() == AL_NO_ERROR), "OpenAL error in alSourcei.");
	}

	ALuint ALSource::GetSource()
	{
		return m_data.sourceID;
	}

	void ALSource::Play()
	{
		alGetSourcei(m_data.sourceID, AL_SOURCE_STATE, &m_data.status);
		if (m_data.sourceID != AL_PLAYING)
		{
			alSourcePlay(m_data.sourceID);
		}
	}

	void ALSource::Pause()
	{
		alGetSourcei(m_data.sourceID, AL_SOURCE_STATE, &m_data.status);
		if (m_data.sourceID == AL_PLAYING)
		{
			alSourcePause(m_data.sourceID);
		}
	}

	void ALSource::Stop()
	{
		alGetSourcei(m_data.sourceID, AL_SOURCE_STATE, &m_data.status);
		if (m_data.sourceID != AL_STOPPED)
		{
			alSourceStop(m_data.sourceID);
		}
	}

	void ALSource::SetVolume(const float volume)
	{
		m_data.gain = volume;
		alSourcef(m_data.sourceID, AL_GAIN, volume);
	}

	void ALSource::SetPitch(const float pitch)
	{
		m_data.pitch = pitch;
		alSourcef(m_data.sourceID, AL_PITCH, pitch);
	}

	void ALSource::SetLooping(const bool looping)
	{
		m_data.looping = looping;
		alSourcei(m_data.sourceID, AL_LOOPING, looping);
	}
}