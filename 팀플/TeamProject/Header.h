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
enum DIRECT {STOP, UP, RIGHT, DOWN, LEFT};

// define
#define PLAYERSPEED 3
#define BULLETSPEED 10
#define BULLETRATE 3

#define WIDTH 1000
#define HEIGHT 800

#define BULLETSIZE 30
#define PLAYERSIZE 50