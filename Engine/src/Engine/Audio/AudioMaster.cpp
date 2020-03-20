#include "AudioMaster.h"
#include "Logging.h"

namespace Engine
{
	void AudioMaster::LoadSound(const std::string& file)
	{
		ALBuffer buffer;

		m_buffers.push_back(buffer);
	}
}
