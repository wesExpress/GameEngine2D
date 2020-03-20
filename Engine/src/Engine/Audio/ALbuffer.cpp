#include "ALBuffer.h"
#include "Logging.h"

namespace Engine
{
	ALBuffer::ALBuffer()
	{
		alGenBuffers(1, &m_buffer);
		ENGINE_INFO("Created OpenAL buffer.");
	}

	ALBuffer::~ALBuffer()
	{
		alDeleteBuffers(1, &m_buffer);
		ENGINE_INFO("Destroyed OpenAL buffer.");
	}

	const ALuint ALBuffer::GetBuffer() const
	{
		return m_buffer;
	}
}