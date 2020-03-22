#include "AudioMaster.h"
#include "Logging.h"
#include "EngineDefines.h"
#include "WaveSample.h"

#include <AL/al.h>

namespace Engine
{
	AudioMaster::AudioMaster()
	{
		int a = 1;
		m_isBigEndian = !((char*)&a)[0];
	}

	void AudioMaster::LoadSound(const std::string& file, const std::string& bufferKey)
	{
		if (!HasBuffer(bufferKey))
		{
			Ref<ALBuffer> buffer(new ALBuffer);

			WaveSample waveSample(file, m_isBigEndian);
			alBufferData(buffer->GetBuffer(), waveSample.GetData().format, waveSample.GetData().data, waveSample.GetData().size, waveSample.GetData().sampleRate);

			m_buffers[bufferKey] = buffer;
		}
		else
		{
			ENGINE_TRACE("Not loading sound as it's already loaded.");
		}
	}

	bool AudioMaster::HasBuffer(const std::string& bufferKey)
	{
		std::unordered_map<std::string, Ref<ALBuffer>>::const_iterator check = m_buffers.find(bufferKey);
		return check != m_buffers.end();
	}

	Ref<ALBuffer> AudioMaster::GetBuffer(const std::string& bufferKey)
	{
		ENGINE_ASSERT(HasBuffer(bufferKey), "Invalid buffer for audioMaster!");
		return m_buffers.at(bufferKey);
	}
}
