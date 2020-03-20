#ifndef __AUDIOMASTER_H__
#define __AUDIOMASTER_H__

#include "ALBuffer.h"

namespace Engine
{
	class AudioMaster
	{
		public:
			void LoadSound(const std::string& file);
		private:
			std::vector<ALBuffer> m_buffers;
	};
}

#endif