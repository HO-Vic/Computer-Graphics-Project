#include "GameSound.h"

GameSound::GameSound()
{
	result = FMOD::System_Create(&soundSystem);
	ERRCHECK(result);
	result = soundSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ERRCHECK(result);
	result = soundSystem->createSound(Common_MediaPath("shootSound.wav"), FMOD_DEFAULT, 0, &shootSound);
	ERRCHECK(result);
	result = shootSound->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	ERRCHECK(result);


	// 반복 사운드
	//FMOD_System_CreateSound(soundSystem, "bgm.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_IntroSound);
	// 효과 사운드
	//FMOD_System_CreateSound(soundSystem, "sound_shoot.wav", FMOD_DEFAULT, 0, &shootSound); //  출력시 //효과는 여러가지 사운드가 있으니 enum과 배열을 이용하여 하자


}

GameSound::~GameSound()
{
	//FMOD_Sound_Release(g_IntroSound);
	//for (int i = 0; i < 6; i++) {
	//	FMOD_Sound_Release(g_IntroSound);//배열일때
	//}
	result = shootSound->release();
	ERRCHECK(result);



	result = soundSystem->close();
	ERRCHECK(result);
	result = soundSystem->release();
	ERRCHECK(result);
	Common_Close();
}

void GameSound::shootingSound()
{
	/*FMOD_System_PlaySound(soundSystem, shootSound, a, 0, &shootChannel);
	
	FMOD_Channel_Stop(shootChannel);*/
	result = soundSystem->playSound(shootSound, 0, false, &shootChannel);
	ERRCHECK(result);
}
