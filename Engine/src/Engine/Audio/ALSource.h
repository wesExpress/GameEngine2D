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
		private:
			ALuint m_source;
	};
}

#endif