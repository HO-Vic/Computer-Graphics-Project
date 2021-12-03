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
	
public:
	GameSound();
	~GameSound();
public:
	void shootingSound();
};