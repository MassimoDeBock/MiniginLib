#pragma once
#include "NullAudioProvider.h"

namespace dae {
	class Locator
	{
	public: 
		static void Initialize();
		static void Destroy();
		static Audio_API& GetAudio();

		static void Provide(Audio_API* service);
	private:
		static Audio_API* m_AudioService;
		static NullAudioProvider nullAudioService;
	};
}

//https://gameprogrammingpatterns.com/service-locator.html