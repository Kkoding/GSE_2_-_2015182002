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

	float x_dir;
	float y_dir;

	int id;

	bool Collision;

	int life;
}MonsterInfo;
