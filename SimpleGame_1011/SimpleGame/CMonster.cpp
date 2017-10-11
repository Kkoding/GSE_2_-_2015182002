#include "stdafx.h"
#include "CMonster.h"
void CMonster::Initialize()
{
	const int moveValue = 5;
	srand((unsigned)time(NULL));
	int xPos = rand() % 3
		;
	if (0 == xPos)
		m_Monster->x_dir = moveValue;
	else if (1 == xPos)
		m_Monster->x_dir = -moveValue;
	else if (2 == xPos)
		m_Monster->x_dir = 0;

	int yPos = rand() % 3;
	if (0 == yPos)
		m_Monster->y_dir = moveValue;
	else if (1 == yPos)
		m_Monster->y_dir = -moveValue;
	else if (2 == yPos)
		m_Monster->y_dir = 0;

}
void CMonster::Update(float fTime)
{
	m_Monster->x += m_Monster->x_dir * fTime;
	m_Monster->y += m_Monster->y_dir * fTime;
}
void CMonster::Render()
{

}
void CMonster::Release()
{

}

CMonster::CMonster()
{
	m_Monster = new MonsterInfo();
	m_Monster->x = 100;
	m_Monster->y = 100;
	m_Monster->z = 0;
	m_Monster->size = 9;
	m_Monster->r = 1;
	m_Monster->g = 0;
	m_Monster->b = 0;
	m_Monster->type = 0;
	m_Monster->a = 0;
	Initialize();
}

CMonster::~CMonster()
{
}
