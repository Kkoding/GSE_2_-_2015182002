#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "winmm.lib") 

using namespace std;

#define MAX_OBJ		500
#define WIDTH		500
#define HEIGHT		500
#define VALUE		0.3

#define BUIL_LIFE			500
#define BUIL_SIZE			100
#define BUIL_SPEED			0
#define BUIL_GAUGE_WIDTH	100
#define BUIL_GAUGE_HEIGHT	10

#define BULL_LIFE			15
#define BULL_SIZE			4
#define BULL_SPEED			200
#define BULL_GAUGE_WIDTH	30
#define BULL_GAUGE_HEIGHT	5

#define ARRO_LIFE		10
#define ARRO_SPEED		300
#define ARROW_SIZE		 4

#define CHAR_LIFE		100
#define CHAR_SIZE		30
#define CHAR_SPEED		300

#define GHOST_LIFE		15
#define GHOST_SIZE		30
#define GHOST_SPEED		200

#define WARI_LIFE		60
#define WARI_SIZE		35
#define WARI_SPEED		250

#define HEALCT_LIFE		150
#define HEALCT_SIZE		 80
#define HEALCT_SPEED	 0

#define HEALKIT_LIFE		10
#define HEALKIT_SIZE		15
#define HEALKIT_SPEED		300

/////////////	OFFICIAL
#include <list>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <vector>

/////////////	NON_OFFICIAL
#include "Enum.h"
#include "struct.h"
#include "Sound.h"
#include "CSceneMgr.h"
#include "Renderer.h"
#include "CObj.h"
#include "CMonster.h"
#include "CBackGround.h"
