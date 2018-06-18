#pragma once
#include <Windows.h>
#include <atlImage.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <iterator>

//#include"resource.h"
using namespace std;

// enum
enum PLAYER_TYPE { PAPER };
enum GAMESTATE  {BATTLE, GAMEPLAY, EXIT,BOSS,TITLE,END};
enum ENEMYSTATE {SPAWN, PLAY, DEAD, DEL, WAIT};
enum DIRECT {STOP, UP, RIGHT, DOWN, LEFT};
enum TYPE {FIRE, WATER, ELEC, GRASS};
enum ANIMATION {START};

#define WIDTH 1000
#define HEIGHT 800

#define BULLETSIZE 30
#define PLAYERSIZE 50