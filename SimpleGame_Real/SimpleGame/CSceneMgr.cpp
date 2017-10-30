#include "stdafx.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_hInstance = NULL;

void CSceneMgr::Update(float fTime)
{

	auto end = (m_lObj).end();
	for (auto begin = (m_lObj).begin(); begin != end; ++begin)
	{
		(*begin)->Update(fTime);
	}
	Check_Coll();
}

void CSceneMgr::Render()
{
	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();

	for (; begin != end; ++begin)
		(*begin)->Render(m_renderer);
}

void CSceneMgr::AddObj(int x, int y)
{
	if (m_lObj.size() < MAX_OBJ)
		m_lObj.push_back(new CMonster(x, y));
}

bool check_coll(CObj* first, CObj* second)
{
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size / 2 &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size / 2 &&
		first->GetInfo()->x + first->GetInfo()->size / 2 >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size / 2 >= second->GetInfo()->y)
	{
		first->SetCollision(TRUE);
		second->SetCollision(TRUE);
		return true;
	}
	return false;
}

void CSceneMgr::Check_Coll()
{

	list<CObj*>::iterator end = m_lObj.end();

	list<CObj*>::iterator end2 = m_lObj.end();

	for (list<CObj*>::iterator start = m_lObj.begin(); start != end; ++start)
	{
		for (list<CObj*>::iterator start2 = m_lObj.begin(); start2 != end2; ++start2)
		{
			if (start != start2 && check_coll((*start), (*start2))) {
				(*start)->SetColor(1, 0, 0);
				(*start2)->SetColor(1, 0, 0);

			}
			else if (start != start2 && false == check_coll((*start), (*start2))) {
				if ((*start)->GetInfo()->Collision == TRUE
					&& (*start2)->GetInfo()->Collision == TRUE) {
					(*start)->SetCollision(FALSE);
					(*start2)->SetCollision(FALSE);
					(*start)->SetColor(1, 1, 1);
					(*start2)->SetColor(1, 1, 1);
				}
			}
		}
	}
}

CSceneMgr::CSceneMgr()
{
	m_renderer = new Renderer(500, 500);
}


CSceneMgr::~CSceneMgr()
{
	delete m_renderer;

}
