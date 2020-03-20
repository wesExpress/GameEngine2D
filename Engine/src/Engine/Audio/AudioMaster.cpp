#include "AudioMaster.h"
#include "Logging.h"

namespace Engine
{
	void AudioMaster::LoadSound(const std::string& file)
	{
		ALBuffer buffer;

		std::string path;
#ifdef __APPLE__
		path = "/Users/wesleypeters/Documents/random_code/GameEngine2D/Application/assets/";
#else
		path = "C:/Users/wcp/source/projects/GameEngine2D/Application/assets/";
#endif

		m_buffers.push_back(buffer);
	}
}