#include "stdafx.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_hInstance = NULL;
extern bool g_gameover;
extern bool b_HealCt;
extern bool b_Help;
extern bool g_gamestart;
extern bool g_Ez;
extern bool g_Hard;
void CSceneMgr::Initialize()
{
	m_fwX = -2;
	m_fwY = 2;
	//////////	빌딩
	CSceneMgr::AddObj(0, (HEIGHT / 2) - 60, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);
	CSceneMgr::AddObj(150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);
	CSceneMgr::AddObj(-150, (HEIGHT / 2) - 150, OBJ_BUILDING, OBJ_TEAM_RED, Red_Building_Rsc);

	CSceneMgr::AddObj(0, -(HEIGHT / 2) + 60, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);
	CSceneMgr::AddObj(150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);
	CSceneMgr::AddObj(-150, -(HEIGHT / 2) + 150, OBJ_BUILDING, OBJ_TEAM_BLUE, Blue_Building_Rsc);
}

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
	int red_monster = rand() % 3;
	// 0 드래곤(하늘), 1 고스트 2전사
	if (m_MakeTime >= 1.f) {
		switch (red_monster) {
		case 0:
			m_lObj.push_back(new CMonster(-(WIDTH / 2) + rand() % (WIDTH + 1), (HEIGHT / 2) - rand() % (HEIGHT / 2 + 1),
				OBJ_CHARACTER, OBJ_TEAM_RED, m_renderer, Red_Dragon_Rsc));
			break;
		case 1:
			m_lObj.push_back(new CMonster(-130 + rand() % 270, 100 + rand() % 201,
				OBJ_GHOST, OBJ_TEAM_RED, m_renderer, Red_Ghost_Rsc));
			break;
		case 2:
			m_lObj.push_back(new CMonster(-130 + rand() % 270, 100 + rand() % 201,
				OBJ_WARRIOR, OBJ_TEAM_RED, m_renderer, Red_Warrior_Rsc));
			break;

		}

		m_MakeTime = 0;
	}


	Collision();

	Check_GameOver();

}

void CSceneMgr::Render(float fTime)
{

	// 배경 (계속해서 그려주자)
	auto Bg_Begin = (m_vBackGround).begin();
	auto Bg_End = (m_vBackGround).end();
	for (; Bg_Begin != Bg_End; Bg_Begin++)
		(*Bg_Begin)->Render(m_renderer);


	if (GS_WIN == m_eGameState) {
		m_renderer->DrawTexturedRectXY(0, 0, 0, 300, 200, 1.f,
			1.f,
			1.f,
			1.f, Win_Rsc, 0.1f);
	}
	else if (GS_LOSE == m_eGameState)
		m_renderer->DrawTexturedRectXY(0, 0, 0, 300, 200, 1.f,
			1.f,
			1.f,
			1.f, Lose_Rsc, 0.1f);

	if (g_gamestart)
		if (b_Help)
		{
			m_renderer->DrawTexturedRectXY(0, 0, 0, 500, 600, 1.f,
				1.f,
				1.f,
				1.f, Help_Rsc, 0.1f);
		}
		else
		{

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
			m_fSnowTime += fTime*0.001f;
			m_fSnowAddTime += m_fSnowTime;
			m_fwX += 0.01;
			m_fwY -= 0.005;
			m_renderer->DrawParticleClimate(0,0, 0, 1, 1, 1, 1, 1, cos(m_fwX),sin(m_fwY) , m_iSnowText, m_fSnowTime, 0.01f);
		}
	else
	{
		if (g_Ez)
			m_renderer->DrawTexturedRectXY(0, 0, 0, 500, 300, 1.f,
				1.f,
				1.f,
				1.f, Ez_Rsc, 0.1f);
		else if (g_Hard)
			m_renderer->DrawTexturedRectXY(0, 0, 0, 500, 300, 1.f,
				1.f,
				1.f,
				1.f, Hard_Rsc, 0.1f);
		else m_renderer->DrawTexturedRectXY(0, 0, 0, 500, 300, 1.f,
			1.f,
			1.f,
			1.f, Mode_Rsc, 0.1f);
	}
}

void CSceneMgr::AddObj(int x, int y, OBJ_TYPE type, OBJ_TEAM team, int iResource)
{
	m_lObj.push_back(new CMonster(x, y, type, team, m_renderer, iResource));
}

void CSceneMgr::AddObj(int ix, int iy, OBJ_TYPE eType, OBJ_TEAM eTeam)
{
	int temp;
	// red blue 생성
	if (OBJ_TEAM_RED == eTeam) {
		if (OBJ_BUILDING == eType)
			temp = Red_Building_Rsc;
		else if (OBJ_CHARACTER == eType)
			temp = Red_Dragon_Rsc;
		else if (OBJ_BULLET == eType)
			temp = Red_Bullet_Rsc;
		else if (OBJ_GHOST == eType)
			temp = Red_Ghost_Rsc;
		else if (OBJ_WARRIOR == eType)
			temp = Red_Warrior_Rsc;
	}
	else
	{
		if (OBJ_BUILDING == eType)
			temp = Blue_Building_Rsc;
		else if (OBJ_CHARACTER == eType)
			temp = Blue_Dragon_Rsc;
		else if (OBJ_BULLET == eType)
			temp = Blue_Bullet_Rsc;
		else if (OBJ_GHOST == eType)
			temp = Blue_Ghost_Rsc;
		else if (OBJ_WARRIOR == eType)
			temp = Blue_Warrior_Rsc;
		else if (OBJ_HEALCENTER == eType)
			temp = Blue_HealCt_Rsc;
		else if (OBJ_HEALKIT == eType)
			temp = Blue_HealKit_Rsc;
	}



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
			m_sound->PlaySound(m_CollBuilding, false, 0.5);
			
			return true;
		}
		if (OBJ_GHOST == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;

			m_sound->PlaySound(m_CollBuilding, false, 0.5);
			return true;
		}
		if (OBJ_GHOST == first->GetInfo()->m_type && OBJ_WARRIOR == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}

		if (OBJ_WARRIOR == first->GetInfo()->m_type && OBJ_ARROW == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}


		if (OBJ_WARRIOR == first->GetInfo()->m_type && OBJ_BULLET == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}
		if (OBJ_WARRIOR == first->GetInfo()->m_type && OBJ_BUILDING == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			m_sound->PlaySound(m_CollBuilding, false, 0.5);
			return true;
		}

		////heal
		if (OBJ_HEALCENTER == first->GetInfo()->m_type && (OBJ_ARROW == second->GetInfo()->m_type)) {
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			if (first->GetInfo()->life < 0)
				b_HealCt = false;
			return true;
		}
		if (OBJ_HEALCENTER == first->GetInfo()->m_type && (OBJ_BULLET == second->GetInfo()->m_type)) {
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			if (first->GetInfo()->life < 0)
				b_HealCt = false;
			return true;
		}

		if (OBJ_HEALCENTER == first->GetInfo()->m_type && (OBJ_WARRIOR == second->GetInfo()->m_type)) {
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			if (first->GetInfo()->life < 0)
				b_HealCt = false;
			return true;
		}
		if (OBJ_HEALCENTER == first->GetInfo()->m_type && (OBJ_CHARACTER == second->GetInfo()->m_type)) {
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			if (first->GetInfo()->life < 0)
				b_HealCt = false;
			return true;
		}


	}
	return false;
}



bool CSceneMgr::SameSollision(CObj* first, CObj* second)
{
	if (first->GetInfo()->life <= 0 || second->GetInfo()->life <= 0)
		return false;
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size &&
		first->GetInfo()->x + first->GetInfo()->size >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size >= second->GetInfo()->y)
	{
		if (OBJ_GHOST == first->GetInfo()->m_type && OBJ_GHOST == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}

		if (OBJ_WARRIOR == first->GetInfo()->m_type && OBJ_WARRIOR == second->GetInfo()->m_type)
		{
			int temphp = first->GetInfo()->life;
			first->GetInfo()->life -= second->GetInfo()->life;
			second->GetInfo()->life -= temphp;
			return true;
		}
	}

}

bool CSceneMgr::Same_Team_Collision(CObj* first, CObj* second)
{
	if (first->GetInfo()->life <= 0 || second->GetInfo()->life <= 0)
		return false;
	if (first->GetInfo()->x <= second->GetInfo()->x + second->GetInfo()->size &&
		first->GetInfo()->y <= second->GetInfo()->y + second->GetInfo()->size &&
		first->GetInfo()->x + first->GetInfo()->size >= second->GetInfo()->x&&
		first->GetInfo()->y + first->GetInfo()->size >= second->GetInfo()->y) {

		if ((OBJ_WARRIOR == (first)->GetInfo()->m_type) && OBJ_HEALKIT == second->GetInfo()->m_type)
		{
			first->GetInfo()->life += second->GetInfo()->life;
			second->GetInfo()->life = 0;
			return true;
		}

		if ((OBJ_CHARACTER == (first)->GetInfo()->m_type) && OBJ_HEALKIT == second->GetInfo()->m_type)
		{
			first->GetInfo()->life += second->GetInfo()->life;
			second->GetInfo()->life = 0;
			return true;
		}
	}

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

			if ((*start)->GetInfo()->m_team != (*start2)->GetInfo()->m_team &&
				(*start)->GetInfo()->m_type == (*start2)->GetInfo()->m_type)
				SameSollision((*start), (*start2));

			if ((*start)->GetInfo()->m_team == (*start2)->GetInfo()->m_team)
				Same_Team_Collision((*start), (*start2));
		}
	}

}

void CSceneMgr::SetResource()
{
	Red_Building_Rsc = m_renderer->CreatePngTexture("Resource/b_3x2_casino.png");
	Red_Dragon_Rsc = m_renderer->CreatePngTexture("Resource/LD.png");
	Red_Bullet_Rsc = m_renderer->CreatePngTexture("Resource/get_coin_01.png");
	Red_Ghost_Rsc = m_renderer->CreatePngTexture("Resource/R_GS.png");
	Red_Warrior_Rsc = m_renderer->CreatePngTexture("Resource/R_War.png");

	Blue_Building_Rsc = m_renderer->CreatePngTexture("Resource/b_3x2_saloon.png");
	Blue_Dragon_Rsc = m_renderer->CreatePngTexture("Resource/RD.png");
	Blue_Bullet_Rsc = m_renderer->CreatePngTexture("Resource/get_coin_02.png");
	Blue_Ghost_Rsc = m_renderer->CreatePngTexture("Resource/B_GS.png");
	Blue_Warrior_Rsc = m_renderer->CreatePngTexture("Resource/B_War.png");

	Win_Rsc = m_renderer->CreatePngTexture("Resource/win.png");
	Lose_Rsc = m_renderer->CreatePngTexture("Resource/lose.png");
	Help_Rsc = m_renderer->CreatePngTexture("Resource/Helper.png");

	Blue_HealCt_Rsc = m_renderer->CreatePngTexture("Resource/b_3x2_fort.png");
	Blue_HealKit_Rsc = m_renderer->CreatePngTexture("Resource/heal_kit.png");

	Mode_Rsc = m_renderer->CreatePngTexture("Resource/Mode.png");
	Ez_Rsc = m_renderer->CreatePngTexture("Resource/ez.png");
	Hard_Rsc = m_renderer->CreatePngTexture("Resource/hd.png");
}

void CSceneMgr::Check_GameOver()
{

	;
	int rb = 0;
	int bb = 0;
	auto ed = m_lObj.end();
	for (auto st = m_lObj.begin(); st != ed; st++) {
		if (OBJ_TEAM_RED == (*st)->GetInfo()->m_team) {
			if (OBJ_BUILDING == (*st)->GetInfo()->m_type) {
				(*st)->GetInfo()->life < 0;
				rb += 1;
			}
		}
		else
		{
			if (OBJ_BUILDING == (*st)->GetInfo()->m_type) {
				(*st)->GetInfo()->life < 0;
				bb += 1;
			}
		}
	}
	if (0 == bb) {
		m_eGameState = GS_LOSE;
		g_gameover = true;
	}
	else if (0 == rb) {
		m_eGameState = GS_WIN;
		g_gameover = true;
	}



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
		if (OBJ_HEALKIT == eType)
			return Blue_HealKit_Rsc;
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
	m_fwX = -2;
	m_fwY = 2;
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
	m_CollBuilding = m_sound->CreateSound("Resource/Scud3.ogg");
	m_eGameState = GS_END;
}



void CSceneMgr::Release()
{
	m_lObj.clear();

	g_gameover = false;
	b_HealCt = false;
	m_eGameState = GS_END;
	
	Initialize();
}


CSceneMgr::~CSceneMgr()
{
	delete m_renderer;
	delete &m_lObj;
}
