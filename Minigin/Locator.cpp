#include "MiniginPCH.h"
#include "Locator.h"

dae::Audio_API* dae::Locator::m_AudioService;
dae::NullAudioProvider dae::Locator::nullAudioService;

void dae::Locator::Initialize()
{
	m_AudioService = &nullAudioService;
}

void dae::Locator::Destroy()
{
	if (m_AudioService != nullptr) {
		delete m_AudioService;
		m_AudioService = nullptr;
	}

}

dae::Audio_API& dae::Locator::GetAudio()
{
	return *m_AudioService;
}

void dae::Locator::Provide(Audio_API* service)
{
	if (service == 0)
	{
		m_AudioService = &nullAudioService;
	}
	else {
		m_AudioService = service;
	}
}
