#pragma once


typedef struct MonsterInfomation
{

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
	int speed;
	OBJ_TYPE m_type;

	float f_Starttime;
	float f_Endtime;

}MonsterInfo;
