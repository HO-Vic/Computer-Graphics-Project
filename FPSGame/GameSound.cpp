#include "GameSound.h"

GameSound::GameSound()
{
	result = FMOD::System_Create(&soundSystem);
//	ERRCHECK(result);
	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
//	ERRCHECK(result);
	result = soundSystem->createSound("sound_shoot.wav", FMOD_DEFAULT, 0, &shootSound);
//	ERRCHECK(result);
	result = shootSound->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
//	ERRCHECK(result);


}

GameSound::~GameSound()
{
	result = shootSound->release();



	result = soundSystem->close();
	result = soundSystem->release();
	//Common_Close();
}

void GameSound::shootingSound()
{
	result = soundSystem->playSound(shootSound, 0, false, &shootChannel);
}
