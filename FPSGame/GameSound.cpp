#include "GameSound.h"

GameSound::GameSound()
{
	result = FMOD::System_Create(&soundSystem);

	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	result = soundSystem->createSound("sound_shoot.wav", FMOD_DEFAULT, 0, &shootSound);
	result = shootSound->setMode(FMOD_LOOP_OFF);

	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	result = soundSystem->createSound("sound_bgm.mp3", FMOD_DEFAULT, 0, &bgmSound);
	result = bgmSound->setMode(FMOD_LOOP_NORMAL);

	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	result = soundSystem->createSound("sound_walk.mp3", FMOD_DEFAULT, 0, &walkSound);
	result = walkSound->setMode(FMOD_LOOP_NORMAL);

	result = soundSystem->playSound(walkSound, 0, false, &walkChannel);
	walkChannel->setVolume(0.6f);
	walkChannel->setPaused(true);

}

GameSound::~GameSound()
{
	result = shootSound->release();
	result = bgmSound->release();
	result = walkSound->release();

	result = soundSystem->close();
	result = soundSystem->release();

	
	//Common_Close();
}

void GameSound::shootingSound()
{
	result = soundSystem->playSound(shootSound, 0, false, &shootChannel);
	shootChannel->setVolume(0.15f);
}

void GameSound::backGroundMusic()
{
	result = soundSystem->playSound(bgmSound, 0, false, &bgmChannel);
	bgmChannel->setVolume(0.03f);
}

void GameSound::walkingSoud()
{
	walkChannel->setPaused(false);
}

void GameSound::pauseWalking()
{
	walkChannel->setPaused(true);
}
