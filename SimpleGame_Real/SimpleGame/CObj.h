#pragma once

class Renderer;
class CObj
{
protected:
	MonsterInfo m_Monster;
public:
	virtual void Initialize() = 0;
	virtual int Update(float) = 0;
	virtual void Render(Renderer*) = 0;
	virtual void Release() = 0;

public:
	MonsterInfo* SetInfo();
	MonsterInfo* GetInfo();
	void SetColor(OBJ_TYPE);
	void SetColor(int, int, int);
	void SetCollision(bool Value) { m_Monster.Collision = Value; }
	
public:
	CObj();
	~CObj();
};