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
	static int bullet_count = 0;
	m_Monster.m_fMakeTime += fTime;
	m_Monster.f_Endtime = GetTickCount();
	if (m_Monster.f_Endtime - m_Monster.f_Starttime > 0.5f)
	{
		if (m_Monster.life <= 0)
			return 1;
		m_Monster.x += m_Monster.x_dir *(m_Monster.speed*0.001);
		m_Monster.y += m_Monster.y_dir *(m_Monster.speed*0.001);

		if (250 - m_Monster.size <= m_Monster.x)
			m_Monster.x_dir *= -1;
		else if (-250 + m_Monster.size >= m_Monster.x)
			m_Monster.x_dir *= -1;

		if (250 <= m_Monster.y + m_Monster.size)
			m_Monster.y_dir *= -1;
		else if (-250 + m_Monster.size >= m_Monster.y)
			m_Monster.y_dir *= -1;

		if (m_Monster.m_fMakeTime > 0.5f)
		{
			if (OBJ_BUILDING == m_Monster.m_type)
			{

				CSceneMgr::Instance()->AddObj(0, 0, OBJ_BULLET, 0);

			}
			if (OBJ_CHARACTER == m_Monster.m_type)
			{
				CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_ARROW, m_Monster.id);
			}
			m_Monster.m_fMakeTime = 0;
		}

		m_Monster.f_Starttime = GetTickCount();
		return 0;
	}
}

void CMonster::Render(Renderer* Rend)
{
	if (m_Monster.life > 0) {
		if (m_Monster.m_type == OBJ_BUILDING)
			Rend->DrawTexturedRect(m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				0,
				0,
				0,
				1.f,
				text_num
			);
		else if (m_Monster.m_type == OBJ_BULLET)
			Rend->DrawTexturedRect(m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				0,
				0,
				0,
				1.f,
				text_num
			);
		else
			Rend->DrawSolidRect(
				m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				1.f
			);
	}
}

void CMonster::Release()
{

}

CMonster::CMonster()
{
	
}

CMonster::CMonster(int x, int y, OBJ_TYPE type, int num)
{
	static int monster_id = 0;
	if (OBJ_BUILDING == type) {
		m_Monster.size = 50;
		m_Monster.life = 500;
		m_Monster.speed = 0;
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 0;
		text_num = m_textBuilding->CreatePngTexture("Resource/Apple.png");
	}
	else if (OBJ_CHARACTER == type) {
		m_Monster.size = 10;
		m_Monster.life = 10;
		m_Monster.speed = 100;
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 1;
		m_Monster.id = ++monster_id;
	}
	else if (OBJ_BULLET == type) {
		m_Monster.size = 10;
		m_Monster.life = 20;
		m_Monster.speed = 300;
		m_Monster.r = 1;
		m_Monster.g = 0;
		m_Monster.b = 0;
		text_num = m_textBuilding->CreatePngTexture("Resource/bullet.png");
	}
	else if (OBJ_ARROW == type) {
		m_Monster.size = 2;
		m_Monster.life = 10;
		m_Monster.speed = 100;
		m_Monster.r = 0;
		m_Monster.g = 1;
		m_Monster.b = 0;
		m_Monster.id = num;
	}

	m_Monster.f_Starttime = GetTickCount();
	m_Monster.x = x;
	m_Monster.y = y;
	m_Monster.z = 0;
	m_Monster.m_type = type;
	m_Monster.a = 0;
	m_Monster.Collision = false;
	m_Monster.m_fMakeTime = 0;
	Initialize();
}

CMonster::~CMonster()
{
}
