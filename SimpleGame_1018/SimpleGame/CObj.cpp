#include "stdafx.h"
#include "CObj.h"
MonsterInfo * CObj::GetInfo()
{
	return &m_Monster;
}

void CObj::SetColor()
{
	m_Monster.r = 1;
	m_Monster.g = 0;
	m_Monster.b = 0;
}


CObj::CObj()
{

}

CObj::~CObj()
{
}

