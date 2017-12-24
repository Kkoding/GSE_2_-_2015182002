#include "stdafx.h"
#include "CMonster.h"

void CMonster::Initialize()
{
	const int moveValue = 5;
	int xPos = rand() % 2;
	if (OBJ_GHOST == m_Monster.m_type) {
		if (m_Monster.x > 0) {
			m_Monster.x_dir = VALUE;
			m_Monster.m_ai = AI_RIGHT;
		}
		else {
			m_Monster.x_dir = -VALUE;

			m_Monster.m_ai = AI_LEFT;
		}
	}
	else
	{
		if (0 == xPos)
			m_Monster.x_dir = VALUE;
		else if (1 == xPos)
			m_Monster.x_dir = -VALUE;
	}


}

int CMonster::Update(float fTime)
{
	float ft = fTime *0.001;

	m_Monster.m_fMakeTime += ft;

	/////	1초마다 체크.
	if (m_Monster.life <= 0)
		return 1;


	switch (m_Monster.m_type)
	{
	case OBJ_GHOST:
		if (AI_RIGHT == m_Monster.m_ai) {
			m_Monster.x += m_Monster.x_dir *(m_Monster.speed*ft);
			if (m_Monster.x > 150) {
				if (OBJ_TEAM_BLUE == m_Monster.m_team) m_Monster.m_ai = AI_UP;
				else m_Monster.m_ai = AI_DOWN;
			}
		}
		else if (AI_LEFT == m_Monster.m_ai) {
			m_Monster.x += m_Monster.x_dir *(m_Monster.speed*ft);
			if (m_Monster.x < -155) {
				if (OBJ_TEAM_BLUE == m_Monster.m_team) m_Monster.m_ai = AI_UP;
				else m_Monster.m_ai = AI_DOWN;
			}
		}
		else if (AI_UP == m_Monster.m_ai) {
			m_Monster.y += m_Monster.y_dir *(m_Monster.speed*ft);
			if (m_Monster.y > 350) {
				m_Monster.x_dir *= -1;
				if (m_Monster.x_dir > 0) m_Monster.m_ai = AI_RIGHT;
				else m_Monster.m_ai = AI_LEFT;
			}
		}
		else if (AI_DOWN == m_Monster.m_ai) {
			m_Monster.y += m_Monster.y_dir *(m_Monster.speed*ft);
			if (m_Monster.y < -350) {
				m_Monster.x_dir *= -1;
				if (m_Monster.x_dir > 0) m_Monster.m_ai = AI_RIGHT;
				else m_Monster.m_ai = AI_LEFT;
			}
		}

		break;
	default:
		m_Monster.x += m_Monster.x_dir *(m_Monster.speed*ft);
		m_Monster.y += m_Monster.y_dir *(m_Monster.speed*ft);
		break;
	}


	if (WIDTH / 2 - m_Monster.size <= m_Monster.x)
		m_Monster.x_dir *= -1;
	else if (-(WIDTH / 2) + m_Monster.size >= m_Monster.x)
		m_Monster.x_dir *= -1;

	if (HEIGHT / 2 <= m_Monster.y + m_Monster.size)
		m_Monster.y_dir *= -1;
	else if (-(HEIGHT / 2) + m_Monster.size >= m_Monster.y)
		m_Monster.y_dir *= -1;

	if (OBJ_BULLET == m_Monster.m_type || OBJ_ARROW == m_Monster.m_type)
	{
		if (WIDTH / 2 - m_Monster.size <= m_Monster.x)
			return 1;
		else if (-(WIDTH / 2) + m_Monster.size >= m_Monster.x)
			return 1;

		if (HEIGHT / 2 <= m_Monster.y + m_Monster.size)
			return 1;
		else if (-(HEIGHT / 2) + m_Monster.size >= m_Monster.y)
			return 1;
	}


	/*
		1초마다 생성 건물에서 총알 생성, 몬스터에서 Arrow 생성.
	*/

	if (OBJ_HEALCENTER == m_Monster.m_type)
	{
		if (m_Monster.m_fMakeTime > 2.f) {
			CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_HEALKIT, OBJ_TEAM_BLUE, CSceneMgr::Instance()->GetResource(m_Monster, OBJ_HEALKIT));
			m_Monster.m_fMakeTime = 0;
		}
	}
	else {

		if (m_Monster.m_fMakeTime > 1.f)
		{
			if (OBJ_BUILDING == m_Monster.m_type)
			{
				if (OBJ_TEAM_RED == m_Monster.m_team) {
					CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_BULLET, OBJ_TEAM_RED, CSceneMgr::Instance()->GetResource(m_Monster, OBJ_BULLET));
				}
				else
					CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_BULLET, OBJ_TEAM_BLUE, CSceneMgr::Instance()->GetResource(m_Monster, OBJ_BULLET));
			}
			if (OBJ_CHARACTER == m_Monster.m_type)
			{
				if (OBJ_TEAM_RED == m_Monster.m_team)
					CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_ARROW, OBJ_TEAM_RED, CSceneMgr::Instance()->GetResource(m_Monster));
				else
					CSceneMgr::Instance()->AddObj(m_Monster.x, m_Monster.y, OBJ_ARROW, OBJ_TEAM_BLUE, CSceneMgr::Instance()->GetResource(m_Monster));
			}

			m_Monster.m_fMakeTime = 0;
		}
	}
	return 0;

}

void CMonster::Render(Renderer* Rend, float fTime)
{
	m_Monster.particle_seconds += fTime*0.01f;

	switch (m_Monster.m_type)
	{
	case OBJ_BUILDING:
		Rend->DrawTexturedRect(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			1.f,
			1.f,
			1.f,
			1.f,
			m_Monster.texture_id,
			0.5f
		);
		//Hp bar
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BUIL_GAUGE_WIDTH,
			BUIL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / BUIL_LIFE,
			0.5f
		);
		Rend->DrawText(
			m_Monster.x,
			m_Monster.y,
			GLUT_BITMAP_HELVETICA_18,
			0, 0, 0, itoa(m_Monster.life, m_transTemp, 10)
		);
		break;
	case OBJ_CHARACTER:
		Rend->DrawTexturedRectSeq(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1,
			m_Monster.texture_id,
			(int)(m_Monster.texture_x) % 4, 0, 4, 1, 0.2f
		);
		m_Monster.texture_x += fTime*0.01f;
		//Hp bar
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BULL_GAUGE_WIDTH,
			BULL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / CHAR_LIFE,
			0.01f
		);
		break;

	case OBJ_BULLET:
		Rend->DrawParticle(m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			1,
			1,
			1,
			1,
			m_Monster.x_dir*(-1), m_Monster.y_dir*(-1),
			m_Monster.texture_id,
			m_Monster.particle_seconds, 0.2f
		);

		Rend->DrawSolidRect(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			m_Monster.a,
			0.3
		);
		break;
	case OBJ_ARROW:
		Rend->DrawSolidRect(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			m_Monster.a,
			0.2
		);
		break;

	case OBJ_GHOST:
		if (m_Monster.x_dir > 0)
			Rend->DrawTexturedRectSeq(
				m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				1,
				m_Monster.texture_id,
				(int)(m_Monster.texture_x) % 2, 0, 4, 1, 0.2f
			);
		else
			Rend->DrawTexturedRectSeq(
				m_Monster.x,
				m_Monster.y,
				0,
				m_Monster.size,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				1,
				m_Monster.texture_id,
				2 + (int)(m_Monster.texture_x) % 2, 0, 4, 1, 0.2f
			);
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BULL_GAUGE_WIDTH,
			BULL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / GHOST_LIFE,
			0.01f
		);
		m_Monster.texture_x += fTime*0.01f;
		break;

	case OBJ_WARRIOR:
		if (m_Monster.x_dir > 0)
			Rend->DrawTexturedRectSeq(
				m_Monster.x,
				m_Monster.y,
				0,
				35,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				1,
				m_Monster.texture_id,
				(int)m_Monster.texture_x % 4, 0, 8, 1, 0.2f
			);
		else
			Rend->DrawTexturedRectSeq(
				m_Monster.x,
				m_Monster.y,
				0,
				35,
				m_Monster.r,
				m_Monster.g,
				m_Monster.b,
				1,
				m_Monster.texture_id,
				4 + (int)m_Monster.texture_x % 4, 0, 8, 1, 0.2f
			);
		m_Monster.texture_x += fTime*0.01f;
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BULL_GAUGE_WIDTH,
			BULL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / WARI_LIFE,
			0.01f);

		break;


	case OBJ_HEALCENTER:
		Rend->DrawTexturedRect(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			1.f,
			1.f,
			1.f,
			1.f,
			m_Monster.texture_id,
			0.1f
		);
		//Hp bar
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BUIL_GAUGE_WIDTH,
			BUIL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / HEALCT_LIFE,
			0.01f
		);
		Rend->DrawText(
			m_Monster.x,
			m_Monster.y,
			GLUT_BITMAP_HELVETICA_18,
			0, 0, 0, itoa(m_Monster.life, m_transTemp, 10)
		);
		break;

	case OBJ_HEALKIT:
		Rend->DrawParticle(m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size/3,
			1,
			1,
			1,
			1,
			0, 0,
			m_Monster.texture_id,
			m_Monster.particle_seconds, 0.2f
		);
		Rend->DrawTexturedRectSeq(
			m_Monster.x,
			m_Monster.y,
			0,
			m_Monster.size,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1,
			m_Monster.texture_id,
			0, 0, 1, 1, 0.2f
		);
		m_Monster.texture_x += fTime*0.01f;
		//Hp barer
		Rend->DrawSolidRectGauge(
			m_Monster.x,
			m_Monster.y + m_Monster.size / 2,
			0,
			BULL_GAUGE_WIDTH / 2,
			BULL_GAUGE_HEIGHT,
			m_Monster.r,
			m_Monster.g,
			m_Monster.b,
			1.f,
			m_Monster.life / HEALKIT_LIFE,
			0.01f
		);
		break;
	}

}

void CMonster::Release()
{

}

CMonster::CMonster()
{

}

CMonster::CMonster(int x, int y, OBJ_TYPE type, OBJ_TEAM team, Renderer* render, int iResource)
{
	m_Monster.x = x;
	m_Monster.y = y;
	m_Monster.z = 0;
	m_Monster.m_type = type;
	m_Monster.Collision = false;
	m_Monster.m_fMakeTime = 0;
	m_Monster.m_team = team;

	if (OBJ_TEAM_RED == m_Monster.m_team) {
		m_Monster.r = 1;
		m_Monster.g = 0;
		m_Monster.b = 0;
		m_Monster.y_dir = -VALUE;
	}
	else {
		m_Monster.r = 0;
		m_Monster.g = 0;
		m_Monster.b = 1;
		m_Monster.y_dir = VALUE;
	}
	m_Monster.a = 1;
	switch (type) {
	case OBJ_BUILDING:
		m_Monster.size = BUIL_SIZE;
		m_Monster.life = BUIL_LIFE;
		m_Monster.speed = BUIL_SPEED;
		if (OBJ_TEAM_RED == team) {
			m_Monster.texture_id = iResource;
		}
		else {
			m_Monster.texture_id = iResource;
		}
		break;

	case OBJ_CHARACTER:
		m_Monster.size = CHAR_SIZE;
		m_Monster.life = CHAR_LIFE;
		m_Monster.speed = CHAR_SPEED;
		if (OBJ_TEAM_RED == team) {
			m_Monster.texture_id = iResource;
		}
		else {
			m_Monster.texture_id = iResource;
		}
		break;
	case OBJ_BULLET:
		m_Monster.size = BULL_SIZE;
		m_Monster.life = BULL_LIFE;
		m_Monster.speed = BULL_SPEED;
		if (OBJ_TEAM_RED == team) {
			m_Monster.texture_id = iResource;
		}
		else {
			m_Monster.texture_id = iResource;
		}
		break;
	case OBJ_ARROW:
		m_Monster.size = ARROW_SIZE;
		m_Monster.life = ARRO_LIFE;
		m_Monster.speed = ARRO_SPEED;
		if (OBJ_TEAM_RED == team) {
			m_Monster.r = 0.5;
			m_Monster.g = 0.2;
			m_Monster.b = 0.7;
			m_Monster.a = 1;
		}
		else {
			m_Monster.r = 1;
			m_Monster.g = 1;
			m_Monster.b = 0;
			m_Monster.a = 1;
		}
		break;
	case OBJ_GHOST:
		m_Monster.size = GHOST_SIZE;
		m_Monster.life = GHOST_LIFE;
		m_Monster.speed = GHOST_SPEED;
		m_Monster.texture_id = iResource;
		m_Monster.a = 1;
		break;
	case OBJ_WARRIOR:
		m_Monster.size = WARI_SIZE;
		m_Monster.life = WARI_LIFE;
		m_Monster.speed = WARI_SPEED;
		m_Monster.texture_id = iResource;
		m_Monster.a = 1;
		break;
	case OBJ_HEALCENTER:
		m_Monster.size = HEALCT_SIZE;
		m_Monster.life = HEALCT_LIFE;
		m_Monster.speed = HEALCT_SPEED;
		m_Monster.texture_id = iResource;
		m_Monster.a = 1;
		break;
	case OBJ_HEALKIT:
		m_Monster.size = HEALKIT_SIZE;
		m_Monster.life = HEALKIT_LIFE;
		m_Monster.speed = HEALKIT_SPEED;
		m_Monster.texture_id = iResource;
		m_Monster.a = 1;
		break;
	}




	m_Monster.texture_x = 0;
	m_Monster.texture_y = 1;
	m_Monster.particle_seconds = 0;
	Initialize();
}

CMonster::~CMonster()
{
}
