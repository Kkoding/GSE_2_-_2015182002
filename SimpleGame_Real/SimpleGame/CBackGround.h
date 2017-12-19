#pragma once
class CBackGround
{
private:
	BackGroundInfo m_tBgInfo;

public:
	void Render(Renderer*);
public:
	CBackGround();
	CBackGround(int, int, int, int, GLuint);
	~CBackGround();
};

