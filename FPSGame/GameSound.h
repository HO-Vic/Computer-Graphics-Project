#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>


class GameSound
{
private:	
	FMOD::System* soundSystem;
	FMOD::Sound* shootSound;
	FMOD::Channel* shootChannel;
	FMOD_RESULT       result;
	void* extradriverdata = 0;
	//FMOD_SYSTEM* soundSystem;
	//FMOD_SOUND* shootSound;

	//FMOD_CHANNEL* shootChannel;

	//FMOD_CHANNELGROUP* a;
	
public:
	GameSound();
	~GameSound();
public:
	void shootingSound();
};