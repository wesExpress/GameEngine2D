#ifndef __AUDIOMASTER_H__
#define __AUDIOMASTER_H__

#include <AL/alc.h>
#include "EngineDefines.h"

namespace Engine
{
	class AudioMaster
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