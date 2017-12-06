#pragma once

class CObj;

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

	float life;
	int speed;
	OBJ_TYPE m_type;
	OBJ_TEAM m_team;

	float f_Starttime;
	float f_Endtime;


	list<CObj*> m_bullet;

	float m_fMakeTime;

	float texture_x;
	int texture_y;
	int texture_id;
	float particle_seconds;
}MonsterInfo;
