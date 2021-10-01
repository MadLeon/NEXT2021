//------------------------------------------------------------------------
//GameManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "GameManager.h"
//------------------------------------------------------------------------

GameManager::GameManager()
{
	m_stateManager = new StateManager();
	m_levelManager = new LevelManager();
	m_itemManager = new ItemManager(m_stateManager, m_levelManager);
	m_enemySpawner = new EnemySpawner(m_itemManager, m_levelManager);
	m_displayManager = new DisplayManager(m_stateManager, m_levelManager, m_itemManager);
	m_inputManager = new InputManager(m_stateManager, m_itemManager, m_enemySpawner);
}

GameManager::~GameManager()
{
	delete m_stateManager;
	delete m_inputManager;
	delete m_displayManager;
	delete m_levelManager;
	delete m_itemManager;
	delete m_enemySpawner;
}

void GameManager::update(float deltaTime)
{
	m_inputManager->Update(deltaTime);

	if (m_levelManager->GetLevelChange())
	{
		m_levelManager->NextLevel();
		m_levelManager->LevelChangeOff();

		m_stateManager->GoldIncrease(100);
		m_enemySpawner->reset();
		m_itemManager->reset();
	}

	if (m_levelManager->GetClear())
		m_stateManager->setState(GameStates::CLEAR);

	if (m_stateManager->getState() == GameStates::PLAYING)
	{
		m_itemManager->Update(deltaTime);
		m_enemySpawner->Update(deltaTime);
	}
	else if (m_stateManager->getState() == GameStates::INTRODUCTION)
	{
		m_stateManager->reset();
		m_enemySpawner->reset();
		m_itemManager->reset();
	}
	else if (m_stateManager->getState() == GameStates::CLEAR)
	{
		m_levelManager->ResetLevel();
		m_levelManager->SetClearOff();

		m_enemySpawner->reset();
		m_itemManager->reset();
	}

}

void GameManager::display() 
{ 
	m_displayManager->display(); 
}