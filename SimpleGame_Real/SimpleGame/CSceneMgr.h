#pragma once

class CObj;
class Renderer;

class CSceneMgr
{
private:
	list<CObj*> m_lObj;
	Renderer * m_renderer;

public:
	void Update(float);
	void Render();
	void AddObj(int, int, OBJ_TYPE);

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

