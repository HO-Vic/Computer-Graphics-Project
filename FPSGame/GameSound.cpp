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

	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	result = soundSystem->createSound("sound_run.mp3", FMOD_DEFAULT, 0, &runSound);
	result = runSound->setMode(FMOD_LOOP_NORMAL);

	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	result = soundSystem->createSound("sound_boss.mp3", FMOD_DEFAULT, 0, &bossSound);
	result = bossSound->setMode(FMOD_LOOP_NORMAL);

	result = soundSystem->playSound(walkSound, 0, false, &walkChannel);
	walkChannel->setVolume(0.6f);
	walkChannel->setPaused(true);
	result = soundSystem->playSound(runSound, 0, false, &runChannel);
	runChannel->setVolume(0.6f);
	runChannel->setPaused(true);
	result = soundSystem->playSound(bossSound, 0, false, &bossChannel);
	bossChannel->setVolume(0.3f);
	bossChannel->setPaused(true);


}

GameSound::~GameSound()
{
	result = shootSound->release();
	result = bgmSound->release();
	result = walkSound->release();
	result = bossSound->release();

	result = soundSystem->close();
	result = soundSystem->release();

	
	//Common_Close();
}

void GameSound::shootingSound()
{
	result = soundSystem->playSound(shootSound, 0, false, &shootChannel);
	shootChannel->setVolume(0.07f);
}

void GameSound::backGroundMusic()
{
	result = soundSystem->playSound(bgmSound, 0, false, &bgmChannel);
	bgmChannel->setVolume(0.03f);
}

void GameSound::walkingSound()
{
	walkChannel->setPaused(false);
}

void GameSound::pauseWalking()
{
	walkChannel->setPaused(true);
}

void GameSound::runningSound()
{
	runChannel->setPaused(false);
}

void GameSound::pauseRunning()
{
	runChannel->setPaused(true);
}

void GameSound::startBossSound()
{
	bossChannel->setPaused(false);
}

void GameSound::pauseBossSound()
{
	bossChannel->setPaused(true);
}
