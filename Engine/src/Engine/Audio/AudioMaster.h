#ifndef __AUDIOMASTER_H__
#define __AUDIOMASTER_H__

#include "ALBuffer.h"
#include "EngineDefines.h"

namespace Engine
{
	class AudioMaster
	{
		public:
			AudioMaster();
			void LoadSound(const std::string& file, const std::string& bufferKey);
			Ref<ALBuffer> GetBuffer(const std::string& bufferKey);
		private:
			char* LoadWAV(const std::string& filename, int& channels, int& sampleRate, int& bitsPerSecond, int& size);
			int CharToInt(char* buffer, int len);
		private:
			std::unordered_map <std::string, Ref<ALBuffer>> m_buffers;
			bool m_isBigEndian;
	};
}

#endif