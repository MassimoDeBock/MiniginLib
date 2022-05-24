#include "MiniginPCH.h"
#include "AudioProvider.h"
#include "SoundEvent.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

struct dae::AudioProvider::Audio_Impl {
	Audio_Impl()
	{
	}
	struct SoundEvent {
		SoundEvent(SoundEventType SoundEvent, int soundID) :m_SoundEvent(SoundEvent), m_SoundID(soundID) {};
		SoundEventType m_SoundEvent;
		int m_SoundID;
	};
	std::thread m_SoundThread;
	std::unordered_map<int, Mix_Chunk*> m_Sounds{};
	std::mutex soundMapMutex;

	std::mutex m;
	std::condition_variable cv;

	std::queue<SoundEvent> m_SoundQueue{};

	//functions
	void ProcessQueue() {
		bool keepThreadRunning {true};
		for (; keepThreadRunning;) {
			std::unique_lock lk(m);
			cv.wait(lk, [&] {return m_SoundQueue.size() > 0; });
			soundMapMutex.lock();
			auto front = m_SoundQueue.front();
			switch (front.m_SoundEvent)
			{
			case dae::SoundEventType::SoundPlay:
				Mix_GroupChannel(Mix_PlayChannel(-1, m_Sounds.find(front.m_SoundID)->second, 0), front.m_SoundID);
				break;
			case dae::SoundEventType::SoundStop:
			{
				int channel{ -1 };
				do {
					channel = Mix_GroupAvailable(front.m_SoundID);
					Mix_GroupChannel(channel, -1); //remove tag
					Mix_HaltChannel(channel);
				} while (channel != -1);
			}
			break;
			case dae::SoundEventType::SoundStopAll:
				Mix_HaltChannel(-1);
				break;
			case dae::SoundEventType::StopThread:
				keepThreadRunning = false;
			default:
				break;
			}
			m_SoundQueue.pop();
			soundMapMutex.unlock();

			lk.unlock();
			cv.notify_all();
		}
		std::cout << "-------------------------\nthread loop ended\n-------------------" << std::endl;
	}
	void SignalThread() {
		cv.notify_all();
	}
};

dae::AudioProvider::AudioProvider()
{
	std::cout << "regular audio provider instansiated" << std::endl;
	pimpl = std::make_unique<AudioProvider::Audio_Impl>();
	pimpl->m_SoundThread = std::thread([this]() {this->pimpl->ProcessQueue(); });
}

dae::AudioProvider::~AudioProvider()
{	
	Destroy();

	for (auto& it : pimpl->m_Sounds) {
		Mix_FreeChunk(it.second);
		it.second=nullptr;
	}
}

void dae::AudioProvider::PlaySound(int soundID)
{
	pimpl->soundMapMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundPlay, soundID));
	pimpl->soundMapMutex.unlock();

	pimpl->SignalThread();
}

void dae::AudioProvider::StopSound(int soundID)
{
	pimpl->soundMapMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundStop, soundID));
	pimpl->soundMapMutex.unlock();
	pimpl->SignalThread();
}

void dae::AudioProvider::StopAllSounds()
{
	pimpl->soundMapMutex.lock();
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::SoundStopAll, 0));
	pimpl->soundMapMutex.unlock();
	pimpl->SignalThread();
}

void dae::AudioProvider::LoadSound(int soundID, const std::string& path)
{
	Mix_Chunk* sample{ Mix_LoadWAV(path.c_str()) };
	if (!sample) {
		std::cout << "error loading sound\n";
		std::cout << Mix_GetError() << std::endl;
	}
	pimpl->m_Sounds.insert(std::make_pair(soundID, sample));
}

void dae::AudioProvider::Destroy()
{
	pimpl->m_SoundQueue.push(Audio_Impl::SoundEvent(SoundEventType::StopThread, 0));
	pimpl->SignalThread();
	pimpl->m_SoundThread.join();
}
