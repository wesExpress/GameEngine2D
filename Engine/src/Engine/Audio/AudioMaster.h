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
			bool HasBuffer(const std::string& bufferKey);
		private:
			std::unordered_map <std::string, Ref<ALBuffer>> m_buffers;
			bool m_isBigEndian;
	};
}

#endif