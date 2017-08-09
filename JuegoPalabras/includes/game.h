#ifndef _H_GAME_
#define _H_GAME_

#include "filereader.h"
#include <thread>
#include <time.h>

enum GameType
{
	TYPE_VS,
	TYPE_AUTO
};

#define MAX_LANGS	2
extern std::string langFiles[MAX_LANGS];

void StartGame(GameType gType, int lang);

#endif