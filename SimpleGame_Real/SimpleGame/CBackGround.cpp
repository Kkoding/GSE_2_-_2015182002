#include "stdafx.h"
#include "CBackGround.h"


void CBackGround::Render(Renderer* render)
{
	render->DrawTexturedRectXY(
		m_tBgInfo.i_xPos,
		m_tBgInfo.i_yPos,
		0,
		m_tBgInfo.i_Texture_xSize,
		m_tBgInfo.i_Texture_ySize,
		1.f,
		1.f,
		1.f,
		1.f,
		m_tBgInfo.i_Texture,
		0.9
	);
}

CBackGround::CBackGround()
{
}

CBackGround::CBackGround(int xPos, int yPos,int Texture_x, int Texture_y, GLuint gl)
{
	m_tBgInfo.i_xPos = xPos;
	m_tBgInfo.i_yPos = yPos;
	m_tBgInfo.i_Texture_xSize = Texture_x;
	m_tBgInfo.i_Texture_ySize = Texture_y;
	m_tBgInfo.i_Texture = gl;
}


CBackGround::~CBackGround()
{
}
