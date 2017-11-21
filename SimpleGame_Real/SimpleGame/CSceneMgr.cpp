#include "stdafx.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_hInstance = NULL;

void CSceneMgr::Update(float fTime)
{
	list<CObj*>::iterator end = (m_lObj).end();
	for (list<CObj*>::iterator begin = (m_lObj).begin(); begin != end;)
	{
		if (1 == ((*begin)->Update(fTime)))
		{
			delete *begin;
			begin = m_lObj.erase(begin);
		}
		else ++begin;
	}

	m_MakeTime += fTime*0.001;
	if (m_MakeTime >= 1.f) {
		m_lObj.push_back(new CMonster(-(WIDTH / 2) + rand() % (WIDTH + 1), (HEIGHT / 2) - rand() % (HEIGHT / 2 + 1), OBJ_CHARACTER, OBJ_TEAM_RED));
		m_MakeTime = 0;
	}


	Collision();

}

void CSceneMgr::Render()
{
	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();

	for (; begin != end; ++begin) {
		(*begin)->Render(m_renderer);
	}
}

void CSceneMgr::AddObj(int x, int y, OBJ_TYPE type, OBJ_TEAM team)
{
	m_lObj.push_back(new CMonster(x, y, type, team));
}




// ´Ù¸¥ÆÀ, ´Ù¸¥Å¸ÀÔ, ÃÑ¾Ë³¢¸® Ãæµ¹ X¤¤
bool CSceneMgr::Check_Collision(CObj* first, CObj* second)
{
	if (first->GetInfo()->life <= 0 || second->GetInfo()->life <= 0)
		return false;
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size &&
		first->GetInfo()->x + first->GetInfo()->size >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size >= second->GetInfo()->y
		||
		second->GetInfo()->x <= first->GetInfo()->x + first->GetInfo()->size &&
		second->GetInfo()->y <= first->GetInfo()->y + first->GetInfo()->size &&
		second->GetInfo()->x + second->GetInfo()->size >= first->GetInfo()->x&&
		second->GetInfo()->y + second->GetInfo()->size >= first->GetInfo()->y
		)
	{
		if (first->GetInfo()->m_team != second->GetInfo()->m_team && first->GetInfo()->m_type != second->GetInfo()->m_type)
		{
			if ((OBJ_BULLET == first->GetInfo()->m_type && OBJ_ARROW == second->GetInfo()->m_type) ||
				(OBJ_ARROW == first->GetInfo()->m_type && OBJ_BULLET == second->GetInfo()->m_type))
				return false;
			else {
				int temphp = first->GetInfo()->life;
				first->GetInfo()->life -= second->GetInfo()->life;
				second->GetInfo()->life -= temphp;
				return true;
			}
		}
	}
	return false;
}



void CSceneMgr::Collision()
{

	list<CObj*>::iterator end = m_lObj.end();
	list<CObj*>::iterator end2 = m_lObj.end();

	for (list<CObj*>::iterator start = m_lObj.begin(); start != end; ++start)
	{
		for (list<CObj*>::iterator start2 = m_lObj.begin(); start2 != end2; ++start2)
		{
			if (start != start2) {
				Check_Collision((*start), (*start2));
			}
		}
	}
}


CSceneMgr::CSceneMgr()
{
	m_renderer = new Renderer(WIDTH, HEIGHT);
	m_MakeTime = 0;

	CSceneMgr::AddObj(0, (HEIGHT / 2) - 50, OBJ_BUILDING, OBJ_TEAM_RED);
	CSceneMgr::AddObj(150, (HEIGHT / 2) - 70, OBJ_BUILDING, OBJ_TEAM_RED);
	CSceneMgr::AddObj(-150, (HEIGHT / 2) - 70, OBJ_BUILDING, OBJ_TEAM_RED);

	CSceneMgr::AddObj(0, -(HEIGHT / 2) + 50, OBJ_BUILDING, OBJ_TEAM_BLUE);
	CSceneMgr::AddObj(150, -(HEIGHT / 2) + 70, OBJ_BUILDING, OBJ_TEAM_BLUE);
	CSceneMgr::AddObj(-150, -(HEIGHT / 2) + 70, OBJ_BUILDING, OBJ_TEAM_BLUE);
}


CSceneMgr::~CSceneMgr()
{
	delete m_renderer;
	delete &m_lObj;
}
