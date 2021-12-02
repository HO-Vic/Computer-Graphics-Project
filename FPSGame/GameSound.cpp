#include "GameSound.h"

GameSound::GameSound()
{
	FMOD_System_Create(&soundSystem, FMOD_VERSION);
	FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, NULL);
	// 반복 사운드
	FMOD_System_CreateSound(soundSystem, "bgm.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_IntroSound);
	// 효과 사운드
	FMOD_System_CreateSound(soundSystem, "shoot.wav", FMOD_DEFAULT, 0, &shoot); //  출력시 //효과는 여러가지 사운드가 있으니 enum과 배열을 이용하여 하자


}

GameSound::~GameSound()
{
	FMOD_Sound_Release(g_IntroSound);
	for (int i = 0; i < 6; i++) {
		FMOD_Sound_Release(g_IntroSound);//배열일때
	}
	FMOD_System_Close(soundSystem);
	FMOD_System_Release(soundSystem);
}
