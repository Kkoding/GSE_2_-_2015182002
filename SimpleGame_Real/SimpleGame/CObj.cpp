#include "stdafx.h"
#include "CObj.h"
MonsterInfo * CObj::GetInfo()
{
	return &m_Monster;
}

void CObj::SetColor(int r, int g , int b)
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

