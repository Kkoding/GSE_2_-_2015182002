#pragma once

class CObj;
class Renderer;
class CBackGround;

class CSceneMgr
{
private:
	list<CObj*> m_lObj;
	Renderer * m_renderer;
	float m_startTime;
	float m_nowTime;
	float m_MakeTime;
	
	
	// ´«
	float m_fSnowTime;
	float m_fSnowAddTime;
	int m_iSnowText;
	float m_fSnowgX;
	float m_fSnowgY;

	// ¹è°æ
	vector<CBackGround*> m_vBackGround;
	int m_itext_num;
	int m_iTree;

	// Sound
	Sound* m_sound;
	int m_collSIndex;
public:
	void Update(float fTime);
	void Render(float);
	void AddObj(int, int, OBJ_TYPE, OBJ_TEAM, char*);
	void AddBackGround(int, int, int, int, char*);
	bool Check_Collision(CObj*, CObj*);
	void Collision();




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

