#include "stdafx.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_hInstance = NULL;

void CSceneMgr::Update(float fTime)
{
	m_startTime = timeGetTime()*0.001;
	list<CObj*>::iterator end = (m_lObj).end();
	for (list<CObj*>::iterator begin = (m_lObj).begin(); begin != end;)
	{
		if (1 == ((*begin)->Update(m_startTime - m_nowTime)))
		{
			delete *begin;
			begin = m_lObj.erase(begin);
		}
		else ++begin;
	}
	Collision();
	m_nowTime = m_startTime;
}

void CSceneMgr::Render()
{
	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();

	for (; begin != end; ++begin) {
		(*begin)->Render(m_renderer);
	}
}

void CSceneMgr::AddObj(int x, int y, OBJ_TYPE type, int num)
{
	m_lObj.push_back(new CMonster(x, y, type, num));
}

bool CSceneMgr::Check_Collision(CObj* first, CObj* second)
{
	if (first->GetInfo()->life <= 0 && second->GetInfo()->life <= 0)
		return false;
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size &&
		first->GetInfo()->x + first->GetInfo()->size  >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size  >= second->GetInfo()->y)
	{

		if (OBJ_BULLET == first->GetInfo()->m_type && OBJ_CHARACTER == second->GetInfo()->m_type)
		{
			second->SetInfo()->life -= first->SetInfo()->life;
			first->SetInfo()->life = 0;
		}

		if (OBJ_ARROW == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			second->SetInfo()->life -= first->SetInfo()->life;
			first->SetInfo()->life = 0;
		}

		if (OBJ_ARROW == first->GetInfo()->m_type && OBJ_CHARACTER == second->GetInfo()->m_type)
		{
			if (first->GetInfo()->id != second->GetInfo()->id) {
				second->SetInfo()->life -= first->SetInfo()->life;
				first->SetInfo()->life = 0;
			}
		}

		if (OBJ_BUILDING == first->GetInfo()->m_type && OBJ_CHARACTER == second->GetInfo()->m_type)
		{
			if (first->GetInfo()->life > 0 && second->GetInfo()->life > 0) {
				first->SetCollision(TRUE);
				first->SetInfo()->life -= second->SetInfo()->life;
				second->SetInfo()->life = 0;
				second->SetCollision(TRUE);
				return true;
			}
			else
				return false;
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
		if ((*start)->GetInfo()->life > 0)
		{
			for (list<CObj*>::iterator start2 = m_lObj.begin(); start2 != end2; ++start2)
			{
				if (start != start2 && Check_Collision((*start), (*start2))) {
					//(*start)->SetColor(1, 0, 0);
				//	(*start2)->SetColor(1, 0, 0);

				}
				else if (start != start2 && false == Check_Collision((*start), (*start2)))
				{
					if ((*start)->GetInfo()->Collision == TRUE
						&& (*start2)->GetInfo()->Collision == TRUE)
					{
						(*start)->SetCollision(FALSE);
						(*start2)->SetCollision(FALSE);
					//	(*start)->SetColor((*start)->GetInfo()->m_type);
					//	(*start2)->SetColor((*start2)->GetInfo()->m_type);
					}
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
	delete &m_lObj;
}
