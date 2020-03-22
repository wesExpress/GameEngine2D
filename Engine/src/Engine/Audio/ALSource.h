#ifndef __ALSOURCE_H__
#define __ALSOURCE_H__

#include <AL/al.h>
#include "AudioMaster.h"

namespace Engine
{
	struct SourceData
	{
		ALuint sourceID;
		ALint status;
		bool looping;
		float pitch;
		float gain;
	};

	class ALSource
	{
		public:
			ALSource();
			~ALSource();

			void SetBuffer(const std::string& filename, const std::string& bufferKey, const Ref<AudioMaster>& audioMaster);

			ALuint GetSource();
			void Play();
			void Pause();
			void Stop();

			void SetVolume(const float volume);
			void SetPitch(const float pitch);
			void SetLooping(const bool loop);
		private:
			SourceData m_data;
	};
}

#endif