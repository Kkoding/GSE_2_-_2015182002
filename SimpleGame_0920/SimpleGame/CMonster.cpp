#include "stdafx.h"
#include "CMonster.h"
void CMonster::Initialize()
{

}
void CMonster::Update()
{
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
}

CMonster::~CMonster()
{
}
