#include "stdafx.h"
#include "CMonster.h"

void CMonster::Initialize()
{
	const int moveValue = 5;
	int xPos = rand() % 2;

	if (0 == xPos)
		m_Monster.x_dir = 3 + rand() % 9;
	else if (1 == xPos)
		m_Monster.x_dir = -(3 + rand() % 9);
	else if (2 == xPos)
		m_Monster.x_dir = 0;

	int yPos = rand() % 2;
	if (0 == yPos)
		m_Monster.y_dir = 3 + rand() % 9;
	else if (1 == yPos)
		m_Monster.y_dir = -(3 + rand() % 9);
	else if (2 == yPos)
		m_Monster.y_dir = 0;
}

int CMonster::Update(float fTime)
{
	m_Monster.x += m_Monster.x_dir *(m_Monster.speed*0.005);
	m_Monster.y += m_Monster.y_dir *(m_Monster.speed*0.005);

	if (250 - m_Monster.size <= m_Monster.x)
		m_Monster.x_dir *= -1;
	else if (-250 + m_Monster.size >= m_Monster.x)
		m_Monster.x_dir *= -1;

	if (250 <= m_Monster.y + m_Monster.size)
		m_Monster.y_dir *= -1;
	else if (-250 + m_Monster.size >= m_Monster.y)
		m_Monster.y_dir *= -1;

	if (m_Monster.m_type == OBJ_BUILDING)
	{
		m_Monster.f_Endtime = GetTickCount();
		
		if (m_Monster.f_Endtime - m_Monster.f_Starttime >0.5f) {
			m_Monster.f_Starttime = GetTickCount();
			CSceneMgr::Instance()->AddObj(0, 0, OBJ_BULLET);
		}
	}

	if (m_Monster.life <= 0)
		return 1;

	return 0;
}

void CMonster::Render(Renderer* Rend)
{
	if (m_Monster.life > 0)
		Rend->DrawSolidRect(
			m_Monster.x,
			m_Monster.y,
			m_Monster.z,
			m_Monster.size,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			m_Monster.a
		);
}

void CMonster::Release()
{

}

CMonster::CMonster()
{

}

CMonster::CMonster(int x, int y, OBJ_TYPE type)
{
	if (OBJ_BUILDING == type) {
		m_Monster.size = 50;
		m_Monster.life = 500;
		m_Monster.speed = 0;
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 0;
		m_Monster.f_Starttime = GetTickCount();
	}
	else if (OBJ_CHARACTER == type) {
		m_Monster.size = 10;
		m_Monster.life = 10;
		m_Monster.speed = 100;
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 1;
	}
	else if (OBJ_BULLET == type) {
		m_Monster.size = 2;
		m_Monster.life = 20;
		m_Monster.speed = 300;
		m_Monster.r = 1;
		m_Monster.g = 0;
		m_Monster.b = 0;
	}
	else if (OBJ_ARROW == type) {
		m_Monster.size = 2;
		m_Monster.life = 10;
		m_Monster.speed = 100;
		m_Monster.r = 0;
		m_Monster.g = 1;
		m_Monster.b = 0;
	}

	static int idd = 0;
	m_Monster.x = x;
	m_Monster.y = y;
	m_Monster.z = 0;
	m_Monster.m_type = type;
	m_Monster.a = 0;
	m_Monster.Collision = false;
	Initialize();
}

CMonster::~CMonster()
{
}
