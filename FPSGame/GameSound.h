#pragma once
//#include<fmod_studio.h>
#include<iostream>
#include<fmod.hpp>
class GameSound
{
private:
	
	FMOD_SYSTEM* soundSystem;
	FMOD_SOUND* g_IntroSound; // 게임 초기 시작시 나오는 배경 음악
	FMOD_SOUND* g_RunSound;	// 게임 진행시 나오는 배경 음악
	FMOD_SOUND* g_FailSound; // 게임 실패시 나오는 배경 음악
	FMOD_SOUND* shoot;

	
	FMOD_CHANNEL* g_RunChannel;
	FMOD_CHANNEL* g_IntroChannel, * g_FailChannel;
	FMOD_CHANNEL* g_pTempChannel;
	
public:
	GameSound();
	~GameSound();
};

