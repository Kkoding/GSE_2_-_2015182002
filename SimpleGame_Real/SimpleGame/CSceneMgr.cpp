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
	m_renderer->DrawTexturedRectXY(
		0,
		0,
		0,
		WIDTH,
		HEIGHT,
		1.f,
		1.f,
		1.f,
		1.f,
		m_itext_num,
		0.9f
	);
	m_renderer->DrawText(
		-(WIDTH / 2),
		HEIGHT / 2 - 20,
		GLUT_BITMAP_HELVETICA_18,
		0, 0, 0, "KDH'S SimpleGame"
	);

	for (; begin != end; ++begin) {
		(*begin)->Render(m_renderer);
	}
}

void CSceneMgr::AddObj(int x, int y, OBJ_TYPE type, OBJ_TEAM team)
{
	m_lObj.push_back(new CMonster(x, y, type, team));
}




// �ٸ���, �ٸ�Ÿ��, �Ѿ˳��� �浹 X��
bool CSceneMgr::Check_Collision(CObj* first, CObj* second)
{
	if (first->GetInfo()->life <= 0 || second->GetInfo()->life <= 0)
		return false;
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size &&
		first->GetInfo()->x + first->GetInfo()->size >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size >= second->GetInfo()->y
		/*||
		second->GetInfo()->x <= first->GetInfo()->x + first->GetInfo()->size &&
		second->GetInfo()->y <= first->GetInfo()->y + first->GetInfo()->size &&
		second->GetInfo()->x + second->GetInfo()->size >= first->GetInfo()->x&&
		second->GetInfo()->y + second->GetInfo()->size >= first->GetInfo()->y*/
		)
	{
		if (OBJ_CHARACTER == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			m_sound->PlaySound(m_collSIndex, false, 0.5);
			return true;
		}

		if (OBJ_BULLET == first->GetInfo()->m_type && OBJ_CHARACTER == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}
		if (OBJ_BULLET == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}
		if (OBJ_ARROW == first->GetInfo()->m_type && OBJ_CHARACTER == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}

		if (OBJ_ARROW == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
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
			if (start != start2 &&
				(*start)->GetInfo()->m_team != (*start2)->GetInfo()->m_team &&
				(*start)->GetInfo()->m_type != (*start2)->GetInfo()->m_type) {
				Check_Collision((*start), (*start2));
			}
		}
	}
}


CSceneMgr::CSceneMgr()
{
	m_renderer = new Renderer(WIDTH, HEIGHT);
	m_MakeTime = 0;

	CSceneMgr::AddObj(0, (HEIGHT / 2) - 60, OBJ_BUILDING, OBJ_TEAM_RED);
	CSceneMgr::AddObj(150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED);
	CSceneMgr::AddObj(-150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED);

	CSceneMgr::AddObj(0, -(HEIGHT / 2) + 60, OBJ_BUILDING, OBJ_TEAM_BLUE);
	CSceneMgr::AddObj(150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE);
	CSceneMgr::AddObj(-150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE);
	m_itext_num = m_textBuilding->CreatePngTexture("Resource/bg.png");
	m_sound = new Sound();

	m_collSIndex = m_sound->CreateSound("Resource/SFX_Monster_Basic_Normal_Die.ogg");
}


CSceneMgr::~CSceneMgr()
{
	delete m_renderer;
	delete &m_lObj;
}
