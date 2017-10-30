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

void CMonster::Update(float fTime)
{
	fTime *= 15;

	m_Monster.x += m_Monster.x_dir * 0.5;
	m_Monster.y += m_Monster.y_dir * 0.5;

	if (250 - m_Monster.size <= m_Monster.x )
		m_Monster.x_dir *= -1;
	else if (-250 + m_Monster.size >= m_Monster.x)
		m_Monster.x_dir *= -1;

	if (250 <= m_Monster.y + m_Monster.size)
		m_Monster.y_dir *= -1;
	else if (-250 + m_Monster.size >= m_Monster.y)
		m_Monster.y_dir *= -1;


}

void CMonster::Render(Renderer* Rend)
{
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

CMonster::CMonster(int x, int y)
{
	static int idd = 0;
	m_Monster.x = x;
	m_Monster.y = y;
	m_Monster.z = 0;
	m_Monster.size = 20+rand()%21;
	m_Monster.r = 1;
	m_Monster.g = 1;
	m_Monster.b = 1;
	m_Monster.type = 0;
	m_Monster.a = 0;
	m_Monster.id = idd++;
	m_Monster.Collision = false;
	m_Monster.life = 10;
	Initialize();
}

CMonster::~CMonster()
{
}
