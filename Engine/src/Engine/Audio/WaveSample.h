#ifndef __WAVEDATA_H__
#define __WAVEDATA_H__

namespace Engine
{
	class WaveSample
	{
		public:
			struct WaveData
			{
				char headerRIFF[4];
				char headerWAVE[4];
				char headerFMT[4];
				size_t headerBITDEPTH;
				size_t headerPCM;
				char headerDATA[4];

				int numChannels;
				int sampleRate;
				int bitsPerSample;
				int size;

				int format;

				char* data;
			};
		public:
			WaveSample(const std::string& filePath, bool isBigEndian);

			int CharToInt(char* buffer, int len, bool isBigEndian);

			const WaveData& GetData() const { return m_data; }
		private:
			WaveData m_data;
	};
}

#endif