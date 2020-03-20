#ifndef __AUDIOBACKEND_H__
#define __AUDIOBACKEND_H__

#include <AL/alc.h>
#include "EngineDefines.h"

namespace Engine
{
	class AudioBackend
	{
		public:
			static void Init();
			static void Shutdown();
		private:
			struct OpenALData
			{
				ALCdevice* device;
				ALCcontext* context;
			};

			static Scope<OpenALData> s_ALData;
	};
}

#endif