#include "ALSource.h"
#include <AL/al.h>

namespace Engine
{
	ALSource::ALSource()
	{
		alGenSources(1, &m_source);
	}

	ALSource::~ALSource()
	{
		alDeleteSources(1, &m_source);
	}

	ALuint ALSource::GetSource()
	{
		return m_source;
	}

	void ALSource::Play()
	{
		alGetSourcei(m_source, AL_SOURCE_STATE, &m_status);
		if (m_status != AL_PLAYING)
		{
			alSourcePlay(m_source);
		}
	}

	void ALSource::Pause()
	{
		alGetSourcei(m_source, AL_SOURCE_STATE, &m_status);
		if (m_status == AL_PLAYING)
		{
			alSourcePause(m_source);
		}
	}

	void ALSource::Stop()
	{
		alGetSourcei(m_source, AL_SOURCE_STATE, &m_status);
		if (m_status != AL_STOPPED)
		{
			alSourceStop(m_source);
		}
	}
}