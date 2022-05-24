#pragma once
#include "Audio_API.h"

namespace dae {
    class AudioProvider final:
        public Audio_API
    {
    public:
        AudioProvider();
        virtual ~AudioProvider();
        virtual void PlaySound(int soundID);
        virtual void StopSound(int soundID);
        virtual void StopAllSounds();
        virtual void LoadSound(int soundID, const std::string& path);

    private:
        void Destroy();
        struct Audio_Impl;
        std::unique_ptr<Audio_Impl> pimpl;
    };
}

//doesn't support music yet