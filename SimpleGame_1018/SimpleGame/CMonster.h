#pragma once

class CObj;
class Renderer;
class CMonster : public CObj
{

public:
	void Initialize();
	void Update(float);
	void Render(Renderer);
	void Release();

public:
	CMonster();
	CMonster(int, int);
	~CMonster();
};