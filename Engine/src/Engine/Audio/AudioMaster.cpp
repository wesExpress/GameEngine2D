#include "AudioMaster.h"

#include <al/al.h>
#include "Logging.h"

namespace Engine
{
	Scope<AudioMaster::OpenALData> AudioMaster::s_ALData = std::make_unique<AudioMaster::OpenALData>(AudioMaster::OpenALData());

	void AudioMaster::Init()
	{
		s_ALData->device = alcOpenDevice(nullptr);

		ENGINE_ASSERT(s_ALData->device, "OpenAL could not be initialized!");
		ENGINE_INFO("OpenAL device: {0}", alcGetString(s_ALData->device, ALC_DEVICE_SPECIFIER));

		s_ALData->context = alcCreateContext(s_ALData->device, nullptr);
		ENGINE_ASSERT(alcMakeContextCurrent(s_ALData->context) == ALC_TRUE, "Could not set an OpenAL context!");
		ENGINE_INFO("OpenAL Info:");
		ENGINE_INFO("	 Version: {0}", alGetString(AL_VERSION));
		ENGINE_INFO("	 Renderer: {0}", alGetString(AL_RENDERER));
		ENGINE_INFO("	 Vendor: {0}", alGetString(AL_VENDOR));
		ENGINE_INFO("	 Extensions: {0}", alGetString(AL_EXTENSIONS));
	}

	void AudioMaster::Shutdown()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(s_ALData->context);
		s_ALData->context = nullptr;

		ENGINE_WARN("Destroying OpenAL context.");

		alcCloseDevice(s_ALData->device);
		s_ALData->device = nullptr;

		ENGINE_WARN("Closing OpenAL device.");
	}
}