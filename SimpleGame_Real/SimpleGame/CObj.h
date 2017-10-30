#pragma once

class Renderer;
class CObj
{
protected:
	MonsterInfo m_Monster;

public:
	virtual void Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render(Renderer*) = 0;
	virtual void Release() = 0;

	MonsterInfo* GetInfo();
	void SetColor(int r,int g,int b);

	void SetCollision(bool Value) { m_Monster.Collision = Value; }
public:
	CObj();
	~CObj();
};