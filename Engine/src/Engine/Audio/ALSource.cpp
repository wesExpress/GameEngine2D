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
}