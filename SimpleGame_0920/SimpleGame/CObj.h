#pragma once
class CObj
{
protected:
	MonsterInfo* m_Monster;
	Renderer* m_Render;

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	MonsterInfo* GetInfo();
public:
	CObj();
	~CObj();
};