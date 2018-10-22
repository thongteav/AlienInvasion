#pragma once

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "fmod.hpp"

class SoundManager
{
public:
	enum SoundEfx
	{
		FAIL,
		SUCCESS,
		SHOOT
	};

	// Member Methods:
public:
	SoundManager();
	~SoundManager();

	bool Initialise();

	void CreateSound(const char* path, FMOD::System* system, FMOD::Sound** sound);
	void PlaySound(SoundManager::SoundEfx sound);
	void PlaySound(FMOD::Sound* sound);

	FMOD::System* GetSystem();
	FMOD::Channel* GetChannel();

protected:

private:
	void CheckFMODResult(FMOD_RESULT result);

	// Member Fields:
public:

protected:
	FMOD::System* m_pSystem;
	FMOD::Channel* m_pChannel;

private:
	FMOD::Sound* m_pSucessSound;
	FMOD::Sound* m_pFailSound;
	FMOD::Sound* m_pShootSound;
};

#endif // !__SOUND_MANAGER_H__
