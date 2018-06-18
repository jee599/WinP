#pragma once
#pragma comment(lib, "winmm.lib" )
#include <Windows.h>
#include <atlImage.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <MMSystem.h>

//#include"resource.h"
using namespace std;

// enum
enum PLAYER_TYPE { PAPER };
enum GAMESTATE  {BATTLE, GAMEPLAY, EXIT,BOSS,TITLE,END,PICK};
enum ENEMYSTATE {SPAWN, PLAY, DEAD, DEL, WAIT};
enum DIRECT {STOP, UP, RIGHT, DOWN, LEFT};
enum PICKTYPE {NONE, FIRE , WATER, ELEC, GRASS};
enum ANIMATION {START};

#define WIDTH 1000
#define HEIGHT 800

#define BULLETSIZE 30
#define PLAYERSIZE 50