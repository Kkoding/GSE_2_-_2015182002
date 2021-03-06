#pragma once

enum OBJ_TYPE {
	OBJ_BUILDING,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_ARROW,
	OBJ_GHOST,
	OBJ_WARRIOR,
	OBJ_HEALCENTER,
	OBJ_HEALKIT,
	OBJ_END
};

enum OBJ_TEAM {
	OBJ_TEAM_RED,
	OBJ_TEAM_BLUE,
};

enum OBJ_aType{
	OBJ_aBuilding,
	OBJ_aGROUND,
	OBJ_aSKY,
	OBJ_aEND
};

enum OBJ_AI {
	AI_UP,
	AI_DOWN,
	AI_RIGHT,
	AI_LEFT,
};

enum OBJ_GAMESTATE {
	GS_WIN,
	GS_LOSE,
	GS_END,
};

enum OBJ_GAMELEVEL {
	GAMELV_NONE,
	GAMELV_EZ,
	GAMELV_HARD,
};

#define WIDTH 500
#define HEIGHT 800