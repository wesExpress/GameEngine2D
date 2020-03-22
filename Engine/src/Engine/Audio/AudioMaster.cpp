#include "AudioMaster.h"
#include "Logging.h"
#include "EngineDefines.h"

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
		Ref<ALBuffer> buffer(new ALBuffer);

		int numChannels, sampleRate, bitsPerSample, size;
		char* data = LoadWAV(file, numChannels, sampleRate, bitsPerSample, size);

		int format;
		if (numChannels == 1)
		{
			if (bitsPerSample == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else if (bitsPerSample == 16)
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else if (numChannels == 2)
		{
			if (bitsPerSample == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else if (bitsPerSample == 16)
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		alBufferData(buffer->GetBuffer(), format, data, size, sampleRate);

		m_buffers[bufferKey] = buffer;
	}

	Ref<ALBuffer> AudioMaster::GetBuffer(const std::string& bufferKey)
	{
		return m_buffers.at(bufferKey);
	}

	char* AudioMaster::LoadWAV(const std::string& filename, int& numChannels, int& sampleRate, int& bitsPerSample, int& size)
	{
		char buffer[4];
		std::ifstream wave(filename, std::ifstream::binary | std::ifstream::in);

		// Make sure wav file has proper RIFF header
		wave.read(buffer, 4);
		ENGINE_ASSERT((memcmp(buffer, "RIFF", 4) == 0), "Problem with wav file hedaer: bad RIFF header");

		// Make sure proper WAVE format
		wave.read(buffer, 4);
		wave.read(buffer, 4);
		ENGINE_ASSERT((memcmp(buffer, "WAVE", 4) == 0), "Problem with wav file header: bad format");

		// Make sure fmt specified
		wave.read(buffer, 4);
		ENGINE_ASSERT((memcmp(buffer, "fmt ", 4) == 0), "Problem with wav file header: bad Subchunk1ID");

		// Make sure 16bit
		const size_t WAV_BIT_DEPTH = 16;
		wave.read(buffer, 4);
		ENGINE_ASSERT((*buffer == WAV_BIT_DEPTH), "Problem with wav file header: bad Subchunk1Size");

		// Make sure file isn't compressed
		const size_t PCM = 1;
		wave.read(buffer, 2);
		ENGINE_ASSERT((*buffer == PCM), "Problem with wav file header: file is compressed");

		// Make sure file is mono or stereo
		const size_t MONO_CHANNELS = 1;
		const size_t STEREO_CHANNELS = 2;
		wave.read(buffer, 2);
		ENGINE_ASSERT(((*buffer == MONO_CHANNELS) || (*buffer == STEREO_CHANNELS)), "Problem with wav file header: bad numChannels");
		numChannels = CharToInt(buffer, 2);

		// Sample Rate
		wave.read(buffer, 4);
		sampleRate = CharToInt(buffer, 4);

		wave.read(buffer, 4);
		wave.read(buffer, 2);

		// bits per sample
		wave.read(buffer, 2);
		bitsPerSample = CharToInt(buffer, 2);

		// Make sure data follows
		wave.read(buffer, 4);
		ENGINE_ASSERT((memcmp(buffer, "data", 4) == 0), "Problem with wav file header: bad Subchunk2ID");

		// Size of data
		wave.read(buffer, 4);
		size = CharToInt(buffer, 4);

		// data
		char* data = new char[size];
		wave.read(data, size);
		return data;
	}

	int AudioMaster::CharToInt(char* buffer, int len)
	{
		int a = 0;

		if (!m_isBigEndian)
		{
			for (int i = 0; i < len; i++)
			{
				((char*)&a)[i] = buffer[i];
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				((char*)&a)[3 - i] = buffer[i];
			}
		}

		return a;
	}
}
