#pragma once


typedef struct MonsterInfomation
{
	int type;

	float x;
	float y;
	float z;
	float size;

	float r;
	float g;
	float b;
	float a;

	int x_dir;
	int y_dir;

	int id;

	bool Collision;

	int life;
}MonsterInfo;
