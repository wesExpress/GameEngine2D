#ifndef __ALBUFFER_H__
#define __ALBUFFER_H__

#include <AL/alc.h>
#include <AL/al.h>

namespace Engine
{
	class ALBuffer
	{
		public:
			ALBuffer();
			~ALBuffer();

			const ALuint GetBuffer() const;
		private:
			ALuint m_buffer;
	};
}

#endif