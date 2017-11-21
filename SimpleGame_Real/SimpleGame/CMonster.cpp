#include "stdafx.h"
#include "CMonster.h"

void CMonster::Initialize()
{
	const int moveValue = 5;
	int xPos = rand() % 2;

	if (0 == xPos)
		m_Monster.x_dir = VALUE;
	else if (1 == xPos)
		m_Monster.x_dir = -VALUE;


	//int yPos = rand() % 2;
	//if (0 == yPos)
	//	m_Monster.y_dir = 3 + rand() % 9;
	//else if (1 == yPos)
	//	m_Monster.y_dir = -(3 + rand() % 9);
	//else if (2 == yPos)
	//	m_Monster.y_dir = 0;

//	m_Monster.x_dir = 1;
//	m_Monster.y_dir = 1;
}

int CMonster::Update(float fTime)
{
	float ft = fTime *0.001;

	m_Monster.m_fMakeTime += ft;

	/////	1초마다 체크.
	if (m_Monster.life <= 0)
		return 1;

	//if (OBJ_CHARACTER != m_Monster.m_type)
	{
		m_Monster.x += m_Monster.x_dir *(m_Monster.speed*ft);
		m_Monster.y += m_Monster.y_dir *(m_Monster.speed*ft);

		if (WIDTH / 2 - m_Monster.size <= m_Monster.x)
			m_Monster.x_dir *= -1;
		else if (-(WIDTH / 2) + m_Monster.size >= m_Monster.x)
			m_Monster.x_dir *= -1;

		if (HEIGHT / 2 <= m_Monster.y + m_Monster.size)
			m_Monster.y_dir *= -1;
		else if (-(HEIGHT / 2) + m_Monster.size >= m_Monster.y)
			m_Monster.y_dir *= -1;
	}

	//////////	1초마다 생성
	if (m_Monster.m_fMakeTime > 1.f)
	{
		if (OBJ_BUILDING == m_Monster.m_type)
		{
			if (OBJ_TEAM_RED == m_Monster.m_team) {
				CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_BULLET, OBJ_TEAM_RED);
				//cout << m_Monster.m_fMakeTime << endl;
			}
			else
				CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_BULLET, OBJ_TEAM_BLUE);
		}
		if (OBJ_CHARACTER == m_Monster.m_type)
		{
			if (OBJ_TEAM_RED == m_Monster.m_team)
				CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_ARROW, OBJ_TEAM_RED);
			else
				CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_ARROW, OBJ_TEAM_BLUE);
		}

		m_Monster.m_fMakeTime = 0;
	}
	return 0;

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
		else
			Rend->DrawSolidRect(m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				m_Monster.a
			);
	}
}

void CMonster::Release()
{

}

CMonster::CMonster()
{

}

CMonster::CMonster(int x, int y, OBJ_TYPE type, OBJ_TEAM team)
{
	static int monster_id = 0;
	m_Monster.x = x;
	m_Monster.y = y;
	m_Monster.z = 0;
	m_Monster.m_type = type;
	m_Monster.Collision = false;
	m_Monster.m_fMakeTime = 0;
	m_Monster.m_team = team;
	if (OBJ_BUILDING == type) {
		m_Monster.size = 100;
		m_Monster.life = 500;
		m_Monster.speed = 0;
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 0;
		if (OBJ_TEAM_RED == team)
			text_num = m_textBuilding->CreatePngTexture("Resource/apple.png");
		else
			text_num = m_textBuilding->CreatePngTexture("Resource/bird.png");
	}
	else if (OBJ_CHARACTER == type) {
		m_Monster.size = 10;
		m_Monster.life = 10;
		m_Monster.speed = 300;
		if (OBJ_TEAM_RED == team) {
			m_Monster.r = 1;
			m_Monster.g = 0;
			m_Monster.b = 0;
			m_Monster.a = 1;
		}
		else {
			m_Monster.r = 0;
			m_Monster.g = 0;
			m_Monster.b = 1;
			m_Monster.a = 1;
		}
	}
	else if (OBJ_BULLET == type) {
		m_Monster.size = 2;
		m_Monster.life = 10;
		m_Monster.speed = 600;
		if (OBJ_TEAM_RED == team) {
			m_Monster.r = 1;
			m_Monster.g = 0;
			m_Monster.b = 0;
			m_Monster.a = 1;
		}
		else {
			m_Monster.r = 0;
			m_Monster.g = 0;
			m_Monster.b = 1;
			m_Monster.a = 1;
		}
		//text_num = m_textBuilding->CreatePngTexture("Resource/bullet.png");
	}
	else if (OBJ_ARROW == type) {
		m_Monster.size = 2;
		m_Monster.life = 10;
		m_Monster.speed = 100;
		if (OBJ_TEAM_RED == team) {
			m_Monster.r = 0.5;
			m_Monster.g = 0.2;
			m_Monster.b = 0.7;
			m_Monster.a = 1;
		}
		else {
			m_Monster.r = 1;
			m_Monster.g = 1;
			m_Monster.b = 0;
			m_Monster.a = 1;
		}


	}
	if (OBJ_TEAM_RED == m_Monster.m_team)
		m_Monster.y_dir = -VALUE;
	else
		m_Monster.y_dir = VALUE;

	
	Initialize();
}

CMonster::~CMonster()
{
}
