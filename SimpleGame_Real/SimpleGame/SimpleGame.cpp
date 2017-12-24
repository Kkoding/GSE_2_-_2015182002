/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

CObj * g_Obj = NULL;
Sound* g_Sound = NULL;

static int g_GhostSnd;
static int g_WarriorSnd;
static int g_HealCtSnd;

const float fTime = 0.1;
static float StartTime = timeGetTime()*0.001;
static float NowTime;
static float elTime;
static float g_preTime = 0;

extern OBJ_TYPE g_Type = OBJ_END;
extern bool g_gameover = false;
extern bool b_HealCt = false;
extern bool b_Help = true;
extern bool g_gamestart = false;
extern bool g_Ez = false;
extern bool g_Hard = false;
extern OBJ_GAMELEVEL g_GameLV = GAMELV_NONE;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.f);


	elTime = timeGetTime();
	if (!b_Help)
	{
		if (!g_gameover)
			CSceneMgr::Instance()->Update(elTime - g_preTime);
	}
	CSceneMgr::Instance()->Render(elTime - g_preTime);

	g_preTime = elTime;
	glutSwapBuffers();
}

void Idle(void)
{

	RenderScene();
}

void MouseMove(int x, int y)
{
	if (260 < y && y < 360) {
		g_Ez = true;
		g_Hard = false;
	}
	else if (440 < y && y < 540) {
		g_Hard = true;
		g_Ez = false;
	}
}

void MouseInput(int button, int state, int x, int y)
{
	static bool button_state = false;

	NowTime = timeGetTime()*0.001f;
	if (!g_gamestart)
	{
		if (g_Ez)
			g_GameLV = GAMELV_EZ;
		else if (g_Hard)
			g_GameLV = GAMELV_HARD;
		g_gamestart = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		button_state = true;



	if (GAMELV_HARD == g_GameLV) 
	{
		if ((NowTime - StartTime) > 2.f) 
		{
			if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
			{
				if (y > 400) 
				{
					CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, OBJ_CHARACTER, OBJ_TEAM_BLUE);

					StartTime = timeGetTime()*0.001;
				}
			}
			if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&  g_Type != OBJ_END) 
			{
				if (OBJ_HEALCENTER == g_Type) {
					if (b_HealCt) return;
					else {
						b_HealCt = true;
						CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, g_Type, OBJ_TEAM_BLUE);
					}
				}

				StartTime = timeGetTime()*0.001;
				CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, g_Type, OBJ_TEAM_BLUE);
			}

		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (y > 400)
			{
				CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, OBJ_CHARACTER, OBJ_TEAM_BLUE);

				StartTime = timeGetTime()*0.001;
			}
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&  g_Type != OBJ_END)
		{
			if (OBJ_HEALCENTER == g_Type) {
				if (b_HealCt) return;
				else {
					b_HealCt = true;
					CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, g_Type, OBJ_TEAM_BLUE);
				}
			}

			StartTime = timeGetTime()*0.001;
			CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, g_Type, OBJ_TEAM_BLUE);
		}
	}

	RenderScene();

}

void KeyInput(unsigned char key, int x, int y)
{

	// 1. À¯·É(°Ç¹°¸¸ °ø°Ý), 2. Àü»ç(¶¥°ø°Ý) 3.ÇÙÆøÅº
	switch (key)
	{
	case '1':
		g_Type = OBJ_GHOST;
		g_Sound->PlaySoundW(g_GhostSnd, false, 10);
		break;

	case '2':
		g_Sound->PlaySoundW(g_WarriorSnd, false, 10);
		g_Type = OBJ_WARRIOR;
		break;

	case '3':
		g_Sound->PlaySoundW(g_HealCtSnd, false, 10);
		g_Type = OBJ_HEALCENTER;
		break;

	case 'r':
	case 'R':
		CSceneMgr::Instance()->Release();
		g_gameover = false;
		break;
	}

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		if (b_Help) {
			b_Help = false;
		}
		else {
			b_Help = true;
		}
		break;
	case GLUT_KEY_F2:
		CSceneMgr::Instance()->Release();
		g_gamestart = false;
		break;
	}
	RenderScene();

}

void Initialize()
{
	g_WarriorSnd = g_Sound->CreateSound("Resource/Attack.ogg");
	g_GhostSnd = g_Sound->CreateSound("Resource/sound_pyromaniac_2.ogg");
	g_HealCtSnd = g_Sound->CreateSound("Resource/sound_healing_1.ogg");
}

int main(int argc, char **argv)
{
	// Initialize GL things

	srand((unsigned)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << " GLEW Version is 3.0\n ";

	else
		std::cout << "GLEW 3.0 not supported\n ";
	g_Obj = new CMonster();

	g_Sound = new Sound();

	Initialize();
	int index = g_Sound->CreateSound("Resource/music_loop1.ogg");

	g_Sound->PlaySoundW(index, true, 1);
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutPassiveMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyInput);


	g_preTime = timeGetTime();
	glutMainLoop();

	return 0;
}

