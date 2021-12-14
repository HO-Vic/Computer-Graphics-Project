#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>


class GameSound
{
private:	
	FMOD::System* soundSystem;
	FMOD::Sound* shootSound;
	FMOD::Channel* shootChannel;

	FMOD::Sound* bgmSound;
	FMOD::Channel* bgmChannel;

	FMOD::Sound* walkSound;
	FMOD::Channel* walkChannel;

	FMOD::Sound* runSound;
	FMOD::Channel* runChannel;

	FMOD::Sound* bossSound;
	FMOD::Channel* bossChannel;

	FMOD_RESULT       result;
	void* extradriverdata = 0;
	
public:
	GameSound();
	~GameSound();
public:
	void shootingSound();
	void backGroundMusic();
	void walkingSound();
	void pauseWalking();
	void runningSound();
	void pauseRunning();
	void startBossSound();
	void pauseBossSound();
};