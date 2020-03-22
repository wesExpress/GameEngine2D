#include "WaveSample.h"
#include "Engine/EngineDefines.h"
#include <AL/al.h>

namespace Engine
{
	WaveSample::WaveSample(const std::string& fileName, bool isBigEndian)
	{
		char buffer[4];
		std::ifstream file(fileName, std::ifstream::binary | std::ifstream::in);

		// Make sure wav file has proper RIFF header
		file.read(m_data.headerRIFF, 4);
		ENGINE_ASSERT((memcmp(m_data.headerRIFF, "RIFF", 4) == 0), "Problem with wav file hedaer: bad RIFF header");

		// Make sure proper WAVE format
		file.ignore(4);
		file.read(m_data.headerWAVE, 4);
		ENGINE_ASSERT((memcmp(m_data.headerWAVE, "WAVE", 4) == 0), "Problem with wav file header: bad format");

		// Make sure fmt specified
		file.read(m_data.headerFMT, 4);
		ENGINE_ASSERT((memcmp(m_data.headerFMT, "fmt ", 4) == 0), "Problem with wav file header: bad Subchunk1ID");

		// Make sure 16bit
		file.read(buffer, 4);
		m_data.headerBITDEPTH = *buffer;
		ENGINE_ASSERT((m_data.headerBITDEPTH == 16), "Problem with wav file header: bad Subchunk1Size");

		// Make sure file isn't compressed
		file.read(buffer, 2);
		m_data.headerPCM = *buffer;
		ENGINE_ASSERT((m_data.headerPCM == 1), "Problem with wav file header: file is compressed");

		// Make sure file is mono or stereo
		file.read(buffer, 2);
		ENGINE_ASSERT(((*buffer == 1) || (*buffer == 2)), "Problem with wav file header: bad numChannels");
		m_data.numChannels = CharToInt(buffer, 2, isBigEndian);

		// Sample Rate
		file.read(buffer, 4);
		m_data.sampleRate = CharToInt(buffer, 4, isBigEndian);

		file.ignore(6);

		// bits per sample
		file.read(buffer, 2);
		m_data.bitsPerSample = CharToInt(buffer, 2, isBigEndian);

		// Make sure data follows
		file.read(m_data.headerDATA, 4);
		ENGINE_ASSERT((memcmp(m_data.headerDATA, "data", 4) == 0), "Problem with wav file header: bad Subchunk2ID");

		// Size of data
		file.read(buffer, 4);
		m_data.size = CharToInt(buffer, 4, isBigEndian);

		// data
		m_data.data = new char[m_data.size];
		file.read(m_data.data, m_data.size);

		switch (m_data.numChannels)
		{
			case 1:
				switch (m_data.bitsPerSample)
				{
					case 8:
						m_data.format = AL_FORMAT_MONO8;
						break;
					case 16:
						m_data.format = AL_FORMAT_MONO16;
						break;
					default:
						ENGINE_ERROR("Invalid bitsPerSample!");
						break;
				}
				break;
			case 2:
				switch (m_data.bitsPerSample)
				{
					case 8:
						m_data.format = AL_FORMAT_STEREO8;
						break;
					case 16:
						m_data.format = AL_FORMAT_STEREO16;
						break;
					default:
						ENGINE_ERROR("Invalid bitsPerSample!");
						break;
				}
				break;
			default:
				ENGINE_ERROR("Invalid number of channels!");
				break;
		}

		file.close();
	}

	int WaveSample::CharToInt(char* buffer, int len, bool isBigEndian)
	{
		int a = 0;

		if (!isBigEndian)
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