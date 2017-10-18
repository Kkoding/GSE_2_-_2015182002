#include "stdafx.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_hInstance = NULL;

void CSceneMgr::Update(float fTime)
{
	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();
	for (; begin != end; ++begin)
	{
		(*begin)->Update(fTime);
	}
	Check_Coll();
}

void CSceneMgr::Render(Renderer Rend)
{
	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();

	for (; begin != end; ++begin)
		(*begin)->Render(Rend);
}

void CSceneMgr::AddObj(int x, int y)
{
	if (m_lObj.size() < MAX_OBJ)
		m_lObj.push_back(new CMonster(x, y));
}

bool check_coll(MonsterInfo* first, MonsterInfo* second)
{

	return true;
}

void CSceneMgr::Check_Coll()
{
	//auto begin = (m_lObj).begin();
	//auto begin2 = (m_lObj).begin();
	//auto end = (m_lObj).end();

	//for (; begin != end; ++begin)
	//{
	//	if (1 < m_lObj.size())
	//	{
	//		for (; begin2 != end; ++begin2)
	//		{
	//			if (check_coll((*begin)->GetInfo(), (*begin2)->GetInfo()))
	//				(*begin)->SetColor();
	//		}
	//	}
	//}
}

CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
}
