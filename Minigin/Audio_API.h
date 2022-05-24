#pragma once

namespace dae {
	class Audio_API
	{
	public:
		virtual ~Audio_API() = default;
		virtual void PlaySound(int soundID) = 0;
		virtual void StopSound(int soundID) = 0;
		virtual void StopAllSounds() = 0;
		virtual void LoadSound(int soundID, const std::string& path) = 0;
	};

}