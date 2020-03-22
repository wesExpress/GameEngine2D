#ifndef __ALSOURCE_H__
#define __ALSOURCE_H__

#include <AL/al.h>

namespace Engine
{
	class ALSource
	{
		public:
			ALSource();
			~ALSource();

			ALuint GetSource();
			void Play();
			void Pause();
			void Stop();
		private:
			ALuint m_source;
			ALint m_status;
	};
}

#endif