//------------------------------------------------------------------------
//InputManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "StateManager.h"
#include "EnemySpawner.h"
#include "ItemManager.h"
#include "InputManager.h"
//------------------------------------------------------------------------

InputManager::InputManager(StateManager* stateManager, ItemManager* itemManager, EnemySpawner* enemySpawner)
{
	m_stateManager = stateManager;
	m_itemManager = itemManager;
	m_enemySpawner = enemySpawner;
}

void InputManager::Update(float deltaTime)
{
	switch (m_stateManager->getState())
	{
	case GameStates::INTRODUCTION:
		introUpdate();
		break;
	case GameStates::PLAYING:
		playingUpdate();
		break;
	case GameStates::PAUSE:
		pauseUpdate();
		break;
	case GameStates::GAMEOVER:
		gameoverUpdate();
		break;
	case GameStates::CLEAR:
		clearupdate();
	}
}

void InputManager::introUpdate()
{
	// ENTER - start
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		m_stateManager->setState(GameStates::PLAYING);
}

void InputManager::playingUpdate()
{
	// BACKSPACE - pause
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_BACK, true))
		m_stateManager->setState(GameStates::PAUSE);

	
	// SPACE / GAMEPAD_A - build tower
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Vec2 mousePos;
		App::GetMousePos(mousePos.x, mousePos.y);
		m_itemManager->BuildTower(TowerType::LASER, mousePos);
	}

	// Enter / GAMEPAD_START - start to spawn enemy
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		m_enemySpawner->Begin();
}

void InputManager::pauseUpdate()
{
	// BACKSPACE - resume
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_BACK, true))
		m_stateManager->setState(GameStates::PLAYING);
}

void InputManager::gameoverUpdate()
{
	// BACKSPACE - exit the game
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_BACK, true))
		exit(0);

	// ENTER - restart
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		m_stateManager->setState(GameStates::INTRODUCTION);
}

void InputManager::clearupdate()
{
	// BACKSPACE - exit the game
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_BACK, true))
		exit(0);

	// ENTER - restart
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
		m_stateManager->setState(GameStates::INTRODUCTION);
}