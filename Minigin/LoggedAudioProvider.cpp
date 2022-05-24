#include "MiniginPCH.h"
#include "LoggedAudioProvider.h"

dae::LoggedAudioProvider::LoggedAudioProvider(Audio_API& wrapped)
	: m_Wrapped(wrapped)
{
	std::cout << "logged audio provider instansiated" << std::endl;
}

dae::LoggedAudioProvider::~LoggedAudioProvider()
{
	delete &m_Wrapped;
}

void dae::LoggedAudioProvider::PlaySound(int soundID)
{
	Log("play sound");
	m_Wrapped.PlaySound(soundID);
}

void dae::LoggedAudioProvider::StopSound(int soundID)
{
	Log("stop sound");
	m_Wrapped.StopSound(soundID);
}

void dae::LoggedAudioProvider::StopAllSounds()
{
	Log("stop all sound");
	m_Wrapped.StopAllSounds();
}

void dae::LoggedAudioProvider::LoadSound(int soundID, const std::string& path)
{
	Log("LoadSound at id");
	Log(path);
	m_Wrapped.LoadSound(soundID, path);
}


void dae::LoggedAudioProvider::Log(const char* message)
{
	std::cout << "AudioLog: \"" << message << "\"\n";
}

void dae::LoggedAudioProvider::Log(const std::string message)
{
	std::cout << "AudioLog: \"" << message << "\"\n";
}
