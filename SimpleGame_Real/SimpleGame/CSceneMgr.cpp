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
			if (*begin) {
				delete *begin;
				(*begin) = NULL;
			}
			begin = m_lObj.erase(begin);
			if (begin == end)
				break;
		}
		else ++begin;
	}

	m_MakeTime += fTime*0.001;
	if (m_MakeTime >= 1.f) {
		m_lObj.push_back(new CMonster(-(WIDTH / 2) + rand() % (WIDTH + 1), (HEIGHT / 2) - rand() % (HEIGHT / 2 + 1),
			OBJ_CHARACTER, OBJ_TEAM_RED, m_renderer, Red_Dragon_Rsc));
		m_MakeTime = 0;
	}


	Collision();

}

void CSceneMgr::Render(float fTime)
{

	// 배경 (계속해서 그려주자)
	auto Bg_Begin = (m_vBackGround).begin();
	auto Bg_End = (m_vBackGround).end();
	for (; Bg_Begin != Bg_End; Bg_Begin++)
		(*Bg_Begin)->Render(m_renderer);




	m_renderer->DrawText(
		-(WIDTH / 2),
		HEIGHT / 2 - 20,
		GLUT_BITMAP_HELVETICA_18,
		0, 0, 0, "KDH'S SimpleGame"
	);

	auto begin = (m_lObj).begin();
	auto end = (m_lObj).end();
	for (; begin != end; ++begin) {
		(*begin)->Render(m_renderer, fTime);
	}
	m_fSnowTime += fTime*0.01f;
	m_fSnowAddTime += m_fSnowTime;



	m_renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.3, -0.3, m_iSnowText, m_fSnowTime, 0.01f);
}

void CSceneMgr::AddObj(int x, int y, OBJ_TYPE type, OBJ_TEAM team, int iResource)
{
	m_lObj.push_back(new CMonster(x, y, type, team, m_renderer, iResource));
}

void CSceneMgr::AddObj(int ix, int iy, OBJ_TYPE eType, OBJ_TEAM eTeam)
{
	int temp;
	if (OBJ_TEAM_RED == eTeam) {
		if (OBJ_BUILDING == eType)
			temp = Red_Building_Rsc;
		else if (OBJ_CHARACTER == eType)
			temp = Red_Dragon_Rsc;
		else if (OBJ_BULLET == eType)
			temp = Red_Bullet_Rsc;
	}
	else
	{
		if (OBJ_BUILDING == eType)
			temp= Blue_Building_Rsc;
		else if (OBJ_CHARACTER == eType)
			temp= Blue_Dragon_Rsc;
		else if (OBJ_BULLET == eType)
			temp= Blue_Bullet_Rsc;
	}

	if (OBJ_GHOST == eType)
		temp = Red_Ghost_Rsc;

	m_lObj.push_back(new CMonster(ix, iy, eType, eTeam, m_renderer, temp));
}

void CSceneMgr::AddBackGround(int ixPos, int iyPos, int iTx, int iTy, char* image_addr)
{
	m_vBackGround.push_back(new CBackGround(ixPos, iyPos, iTx, iTy, m_renderer->CreatePngTexture(image_addr)));
}

// 다른팀, 다른타입, 총알끼리 충돌 Xㄴ
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

void CSceneMgr::SetResource()
{
	Red_Building_Rsc = m_renderer->CreatePngTexture("Resource/b_3x2_casino.png");
	Red_Dragon_Rsc = m_renderer->CreatePngTexture("Resource/LD.png");
	Red_Bullet_Rsc = m_renderer->CreatePngTexture("Resource/get_coin_01.png");
	Red_Ghost_Rsc = m_renderer->CreatePngTexture("Resource/Red_Ghost.png");

	Blue_Building_Rsc = m_renderer->CreatePngTexture("Resource/b_3x2_saloon.png");
	//Blue_Dragon_Rsc = m_renderer->CreatePngTexture("Resource/Red_Ghost.png");
	Blue_Dragon_Rsc = m_renderer->CreatePngTexture("Resource/RD.png");
	Blue_Bullet_Rsc = m_renderer->CreatePngTexture("Resource/get_coin_02.png");
}

int CSceneMgr::GetResource(MonsterInfo& Info, OBJ_TYPE eType)
{
	if (OBJ_TEAM_RED == Info.m_team) {
		if (OBJ_BUILDING == eType)
			return Red_Building_Rsc;
		if (OBJ_CHARACTER == eType)
			return Red_Dragon_Rsc;
		if (OBJ_BULLET == eType)
			return Red_Bullet_Rsc;
	}
	else
	{
		if (OBJ_BUILDING == eType)
			return Blue_Building_Rsc;
		if (OBJ_CHARACTER == eType)
			return Blue_Dragon_Rsc;
		if (OBJ_BULLET == eType)
			return Blue_Bullet_Rsc;
	}
}


int CSceneMgr::GetResource(MonsterInfo& Info)
{
	if (OBJ_TEAM_RED == Info.m_team) {
		if (OBJ_BUILDING == Info.m_type)
			return Red_Building_Rsc;
		if (OBJ_CHARACTER == Info.m_type)
			return Red_Dragon_Rsc;
		if (OBJ_BULLET == Info.m_type)
			return Red_Bullet_Rsc;
	}
	else
	{
		if (OBJ_BUILDING == Info.m_type)
			return Blue_Building_Rsc;
		if (OBJ_CHARACTER == Info.m_type)
			return Blue_Dragon_Rsc;
		if (OBJ_BULLET == Info.m_type)
			return Blue_Bullet_Rsc;
	}
}


CSceneMgr::CSceneMgr()
{
	m_renderer = new Renderer(WIDTH, HEIGHT);
	m_MakeTime = 0;
	m_fSnowTime = 0;
	SetResource();
	//////////	빌딩
	CSceneMgr::AddObj(0, (HEIGHT / 2) - 60, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);
	CSceneMgr::AddObj(150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);
	CSceneMgr::AddObj(-150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);

	CSceneMgr::AddObj(0, -(HEIGHT / 2) + 60, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);
	CSceneMgr::AddObj(150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);
	CSceneMgr::AddObj(-150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);

	/////////	배경 오브젝트
	AddBackGround(0, 0, WIDTH, HEIGHT, "Resource/bg.png");
	AddBackGround(0, 0, 48, 84, "Resource/e_1x1_tree.png");
	AddBackGround(190, 50, 48, 84, "Resource/e_1x2_bones.png");
	AddBackGround(-120, -80, 48, 66, "Resource/e_1x1_rocks_a.png");
	AddBackGround(-120, 80, 48, 66, "Resource/e_1x1_cactus_a.png");

	m_iSnowText = m_renderer->CreatePngTexture("Resource/explosion_01.png");
	m_sound = new Sound();
	m_fSnowgX = -0.1;
	m_fSnowgY = -0.1;
	m_collSIndex = m_sound->CreateSound("Resource/SFX_Monster_Basic_Normal_Die.ogg");
}


CSceneMgr::~CSceneMgr()
{
	delete m_renderer;
	delete &m_lObj;
}
