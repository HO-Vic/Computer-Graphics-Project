#pragma once
//#include<fmod_studio.h>
#include<iostream>
#include<fmod.hpp>
class GameSound
{
private:
	
	FMOD_SYSTEM* soundSystem;
	FMOD_SOUND* g_IntroSound; // ���� �ʱ� ���۽� ������ ��� ����
	FMOD_SOUND* g_RunSound;	// ���� ����� ������ ��� ����
	FMOD_SOUND* g_FailSound; // ���� ���н� ������ ��� ����
	FMOD_SOUND* shoot;

	
	FMOD_CHANNEL* g_RunChannel;
	FMOD_CHANNEL* g_IntroChannel, * g_FailChannel;
	FMOD_CHANNEL* g_pTempChannel;
	
public:
	GameSound();
	~GameSound();
};

