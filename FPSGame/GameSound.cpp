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


	// �ݺ� ����
	//FMOD_System_CreateSound(soundSystem, "bgm.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_IntroSound);
	// ȿ�� ����
	//FMOD_System_CreateSound(soundSystem, "sound_shoot.wav", FMOD_DEFAULT, 0, &shootSound); //  ��½� //ȿ���� �������� ���尡 ������ enum�� �迭�� �̿��Ͽ� ����


}

GameSound::~GameSound()
{
	//FMOD_Sound_Release(g_IntroSound);
	//for (int i = 0; i < 6; i++) {
	//	FMOD_Sound_Release(g_IntroSound);//�迭�϶�
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
