#pragma once

class CObj;
class Renderer;

class CSceneMgr
{
private:
	list<CObj*> m_lObj;
	MonsterInfo Monster[50];
public:
	void Update(float);
	void Render(Renderer);
	void AddObj(int, int);

	void Check_Coll();

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

