#pragma once

class CObj;
class Renderer;
class CMonster : public CObj
{
private:
	char m_transTemp[10];

public:
	void Initialize();
	int Update(float);
	void Render(Renderer*, float);
	void Release();

public:
	CMonster();
	CMonster(int, int,OBJ_TYPE, OBJ_TEAM, Renderer*, int);
	~CMonster();
};

