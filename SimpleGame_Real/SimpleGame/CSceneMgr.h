#pragma once

class CObj;
class Renderer;
class CBackGround;

class CSceneMgr
{
private:
	list<CObj*> m_lObj;
	Renderer * m_renderer;


	float m_fwX;
	float m_fwY;

	float m_startTime;
	float m_nowTime;
	float m_MakeTime;


	// 눈
	float m_fSnowTime;
	float m_fSnowAddTime;
	int m_iSnowText;
	float m_fSnowgX;
	float m_fSnowgY;

	// 배경
	vector<CBackGround*> m_vBackGround;
	int m_itext_num;
	int m_iTree;

	// Sound
	Sound* m_sound;
	int m_collSIndex;
	int m_CollBuilding;
	int m_HealKitSnd;

	// 리소스
	int Red_Building_Rsc;
	int Red_Dragon_Rsc;
	int Red_Bullet_Rsc;
	int Red_Ghost_Rsc;
	int Red_Warrior_Rsc;

	int Blue_Building_Rsc;
	int Blue_Dragon_Rsc;
	int Blue_Bullet_Rsc;
	int Blue_Ghost_Rsc;
	int Blue_Warrior_Rsc;

	int Win_Rsc;
	int Lose_Rsc;
	int Help_Rsc;

	int Mode_Rsc;
	int Ez_Rsc;
	int Hard_Rsc;
	OBJ_GAMESTATE m_eGameState;

	int Blue_HealCt_Rsc;
	int Blue_HealKit_Rsc;

public:
	int GetResource(MonsterInfo&);
	int GetResource(MonsterInfo&, OBJ_TYPE);



public:
	void Initialize();
	void Update(float fTime);
	void Render(float);
	void AddObj(int, int, OBJ_TYPE, OBJ_TEAM, int);
	void AddObj(int, int, OBJ_TYPE, OBJ_TEAM);
	void AddBackGround(int, int, int, int, char*);
	void Collision();

	bool Check_Collision(CObj*, CObj*);
	bool SameSollision(CObj*, CObj*);

	bool Same_Team_Collision(CObj*, CObj*);

	void SetResource();
	void Check_GameOver();

	void Release();

private:
	static CSceneMgr* m_hInstance;
public:
	static CSceneMgr* Instance()
	{
		if (NULL == m_hInstance)
			m_hInstance = new CSceneMgr();
		return m_hInstance;
	}

	void Destroy()
	{
		if (NULL != m_hInstance)
		{
			m_hInstance = NULL;
			delete m_hInstance;
		}
	}

private:
	CSceneMgr();

public:
	~CSceneMgr();
};

