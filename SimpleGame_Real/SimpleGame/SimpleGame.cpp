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

const float fTime = 0.1;
static float StartTime = timeGetTime()*0.001;
static float NowTime;
static float elTime;
static float g_preTime = 0;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.f);


	CSceneMgr::Instance()->Render();

	glutSwapBuffers();
}

void Idle(void)
{
	elTime = timeGetTime();
	CSceneMgr::Instance()->Update(elTime - g_preTime);

	g_preTime = elTime;
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	static bool button_state = false;

	NowTime = timeGetTime()*0.001f;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		button_state = true;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (button_state && (NowTime - StartTime) > 2.f) {
			//cout << NowTime - StartTime << endl;
			if (y > 400) {
				CSceneMgr::Instance()->AddObj(x - (WIDTH / 2), (HEIGHT / 2) - y, OBJ_CHARACTER, OBJ_TEAM_BLUE);
				StartTime = timeGetTime()*0.001;
			}
		}
		button_state = false;
	}


	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
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

	int index = g_Sound->CreateSound("Resource/BGM_Prepare.ogg");

	g_Sound->PlaySoundW(index, true, 1);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);


	g_preTime = timeGetTime() ;
	glutMainLoop();

	return 0;
}

