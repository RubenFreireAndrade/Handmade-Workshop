#pragma once

/*===================================================================#
| 'Game' source files last updated on 19 May 2021                    |
#===================================================================*/

#include <deque>
#include <string>
#include "GameState.h"

//TODO - Refine class such that it follows newer design

class Game
{

public:

	Game();

	int GetTotalTime();
	int GetElapsedTime();

	bool Initialize(const std::string& name, int screenWidth, int screenHeight,
		int pixelsPerUnit = 1, bool isFullscreen = false);

	void AddState(GameState* state);
	void ChangeState(GameState* state);

	bool Run();
	void ShutDown();

private:

	void RemoveState();

	bool m_endGame;
	int m_deltaTime;
	std::deque<GameState*> m_gameStates;

};