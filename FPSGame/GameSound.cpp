#include "GameSound.h"

GameSound::GameSound()
{
	FMOD_System_Create(&soundSystem, FMOD_VERSION);
	FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, NULL);
	// �ݺ� ����
	FMOD_System_CreateSound(soundSystem, "bgm.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_IntroSound);
	// ȿ�� ����
	FMOD_System_CreateSound(soundSystem, "shoot.wav", FMOD_DEFAULT, 0, &shoot); //  ��½� //ȿ���� �������� ���尡 ������ enum�� �迭�� �̿��Ͽ� ����


}

GameSound::~GameSound()
{
	FMOD_Sound_Release(g_IntroSound);
	for (int i = 0; i < 6; i++) {
		FMOD_Sound_Release(g_IntroSound);//�迭�϶�
	}
	FMOD_System_Close(soundSystem);
	FMOD_System_Release(soundSystem);
}
