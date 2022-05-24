#pragma once
#include "Audio_API.h"

namespace dae {
	class LoggedAudioProvider :
		public Audio_API
	{
	public:
		LoggedAudioProvider(Audio_API& wrapped);
		virtual ~LoggedAudioProvider();
		virtual void PlaySound(int soundID);
		virtual void StopSound(int soundID);
		virtual void StopAllSounds();
		virtual void LoadSound(int soundID, const std::string& path);

	private:
		void Log(const char* message);
		void Log(const std::string message);
		
		Audio_API &m_Wrapped;
	};
}
