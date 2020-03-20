#include "ALBuffer.h"
#include "Logging.h"

namespace Engine
{
	ALBuffer::ALBuffer()
	{
		alGenBuffers(1, &m_buffer);
		ENGINE_TRACE("Created OpenAL buffer.");
	}

	ALBuffer::~ALBuffer()
	{
		alDeleteBuffers(1, &m_buffer);
		ENGINE_WARN("Destroyed OpenAL buffer.");
	}

	const ALuint ALBuffer::GetBuffer() const
	{
		return m_buffer;
	}
}
