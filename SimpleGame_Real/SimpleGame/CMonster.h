#pragma once

class CObj;
class Renderer;
class CMonster : public CObj
{
private:
	int text_num;
	Renderer* m_textBuilding;
	char m_transTemp[10];
public:
	void Initialize();
	int Update(float);
	void Render(Renderer*);
	void Release();

public:
	CMonster();
	CMonster(int, int,OBJ_TYPE, OBJ_TEAM);
	~CMonster();
};