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
enum GAMESTATE  {CHANGE, GAMEPLAY, EXIT,TITLE};
enum ENEMYSTATE {SPAWN, PLAY, DEAD, DEL};
enum DIRECT {STOP, UP, RIGHT, DOWN, LEFT};
enum TYPE {FIRE, WATER, ELEC, GRASS};
enum ANIMATION {START};

// define
#define PLAYERSPEED 3
#define BULLETSPEED 10
#define BULLETRATE 5

#define WIDTH 1000
#define HEIGHT 800

#define BULLETSIZE 30
#define PLAYERSIZE 50