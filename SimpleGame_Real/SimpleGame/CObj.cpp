#include "stdafx.h"
#include "CObj.h"
MonsterInfo * CObj::GetInfo()
{
	return &m_Monster;
}

MonsterInfo * CObj::SetInfo()
{
	return &m_Monster;
}

void CObj::SetColor(OBJ_TYPE type)
{
	if (OBJ_BUILDING == type) {
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 0;
	}
	else if (OBJ_CHARACTER == type) {
		m_Monster.r = 1;
		m_Monster.g = 1;
		m_Monster.b = 1;
	}
	else if (OBJ_BULLET == type) {
		m_Monster.r = 1;
		m_Monster.g = 0;
		m_Monster.b = 0;
	}
	else if (OBJ_ARROW == type) {
		m_Monster.r = 0;
		m_Monster.g = 1;
		m_Monster.b = 0;
	}


}

void CObj::SetColor(int r, int g, int b)
{
	m_Monster.r = r;
	m_Monster.g = g;
	m_Monster.b = b;
}

CObj::CObj()
{

}

CObj::~CObj()
{
}

