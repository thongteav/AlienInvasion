// This include:
#include "SoundManager.h"

// Local includes:
#include "LogManager.h"

// Library includes:
#include <SDL.h>

SoundManager::SoundManager()
: m_pSystem(0)
, m_pChannel(0)
, m_pFailSound(0)
, m_pSucessSound(0)
{

}

SoundManager::~SoundManager()
{
	m_pFailSound->release();
	m_pSucessSound->release();
	m_pSystem->release();
}

bool
SoundManager::Initialise()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_pSystem);
	CheckFMODResult(result);

	result = m_pSystem->init(512, FMOD_INIT_NORMAL, 0);
	CheckFMODResult(result);

	CreateSound("..\\..\\Gold Build - 14883251\\Bin\\assets\\sounds\\fail.wav", m_pSystem, &m_pFailSound);
	CreateSound("..\\..\\Gold Build - 14883251\\Bin\\assets\\sounds\\success.wav", m_pSystem, &m_pSucessSound);
	CreateSound("..\\..\\Gold Build - 14883251\\Bin\\assets\\sounds\\shoot.wav", m_pSystem, &m_pShootSound);
	return (true);
}

void
SoundManager::CheckFMODResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		LogManager::GetInstance().Log("FMOD error!\n");
		exit(-1);
	}
}

void
SoundManager::CreateSound(const char* path, FMOD::System* system, FMOD::Sound** sound)
{
	FMOD_RESULT result = system->createSound(path, FMOD_LOOP_OFF, 0, sound);
	CheckFMODResult(result);
}

void
SoundManager::PlaySound(SoundManager::SoundEfx sound)
{
	switch (sound)
	{
		case SoundManager::FAIL:
			PlaySound(m_pFailSound);
			break;
		case SoundManager::SUCCESS:
			PlaySound(m_pSucessSound);
			break;
		case SoundManager::SHOOT:
			PlaySound(m_pShootSound);
			break;
	}
}

void
SoundManager::PlaySound(FMOD::Sound* sound)
{
	m_pSystem->playSound(sound, 0, false, &m_pChannel);
}

FMOD::System*
SoundManager::GetSystem()
{
	return (m_pSystem);
}

FMOD::Channel*
SoundManager::GetChannel()
{
	return (m_pChannel);
}