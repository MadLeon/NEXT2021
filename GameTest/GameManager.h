//------------------------------------------------------------------------
//GameManager.h
//------------------------------------------------------------------------
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
//------------------------------------------------------------------------
#include "StateManager.h"
#include "LevelManager.h"
#include "ItemManager.h"
#include "DisplayManager.h"
#include "EnemySpawner.h"
#include "InputManager.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Game management class, responsible for controlling the entire game process
//------------------------------------------------------------------------
class GameManager
{
	StateManager* m_stateManager;
	InputManager* m_inputManager;
	LevelManager* m_levelManager;
	DisplayManager* m_displayManager;
	ItemManager* m_itemManager;
	EnemySpawner* m_enemySpawner;

public:

	GameManager();
	~GameManager();
	void update(float);
	void display();
};

#endif // !_GAMEMANAGER_H