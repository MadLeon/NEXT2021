//------------------------------------------------------------------------
//DisplayManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "StateManager.h"
#include "ItemManager.h"
#include "LevelManager.h"
#include "DisplayManager.h"
//------------------------------------------------------------------------

DisplayManager::DisplayManager(StateManager* stateManager, LevelManager* levelManager, ItemManager* itemManager)
{	
	m_stateManager = stateManager;
	m_levelManager = levelManager;
	m_itemManager = itemManager;
}

void DisplayManager::display()
{
	switch (m_stateManager->getState())
	{
	case GameStates::INTRODUCTION:
		introScreen();
		break;
	case GameStates::PLAYING:
		playingScreen();
		break;
	case GameStates::PAUSE:
		pauseScreen();
		break;
	case GameStates::GAMEOVER:
		gameoverScreen();
		break;
	case GameStates::CLEAR:
		clearSreen();
		break;
	}
}

void DisplayManager::introScreen()
{
	// print title
	App::Print((APP_VIRTUAL_WIDTH - TITLE_LENGTH) / 2, APP_VIRTUAL_HEIGHT / 2 + 80,
		GAME_TITLE, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	// print instruction
	App::Print((APP_VIRTUAL_WIDTH - 178) / 2, 400,
		"PRESS ENTER TO START", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
}

void DisplayManager::playingScreen()
{
	displayGameUI();

	m_levelManager->DrawMap();
	m_itemManager->Draw();
}

void DisplayManager::pauseScreen()
{
	App::Print((APP_VIRTUAL_WIDTH - 255) / 2, APP_VIRTUAL_HEIGHT / 2 + 80,
		"THE GAME IS PAUSED", 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print((APP_VIRTUAL_WIDTH - 177) / 2, 400,
		"RESUME - BACKSPACE", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
}

void DisplayManager::gameoverScreen()
{
	App::Print((APP_VIRTUAL_WIDTH - 114) / 2, APP_VIRTUAL_HEIGHT / 2 + 80,
		"GAME OVER", 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print((APP_VIRTUAL_WIDTH - 134) / 2, 400,
		"RESTART - ENTER", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);

	App::Print((APP_VIRTUAL_WIDTH - 134) / 2, 370,
		"EXIT - BACKSPACE", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
}

void DisplayManager::clearSreen()
{
	App::Print((APP_VIRTUAL_WIDTH - 246) / 2, APP_VIRTUAL_HEIGHT / 2 + 80,
		"CONGRATULATIONS!", 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print((APP_VIRTUAL_WIDTH - 134) / 2, 400,
		"RESTART - ENTER", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);

	App::Print((APP_VIRTUAL_WIDTH - 134) / 2, 370,
		"EXIT - BACKSPACE", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
}

// for testing purpose
void DisplayManager::textTestScreen()
{
	const char sample[] = "the quick brown fox jumps over the lazy dog, THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
	const char num1[] = "9 By 15";
	const char num2[] = "8 By 13";
	const char roman10[] = "Roman10";
	const char roman24[] = "Roman24";
	const char helvetica10[] = "Helvetica10";
	const char helvetica12[] = "Helvetica12";
	const char helvetica18[] = "Helvetica18";

	const int x1 = 20;
	const int x2 = 150;

	App::Print(x1, 668, num1, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(x2, 668, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(x1, 648, num2, 1.0, 1.0, 1.0, GLUT_BITMAP_8_BY_13);
	App::Print(x2, 648, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_8_BY_13);
	App::Print(x1, 628, roman10, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_10);
	App::Print(x2, 628, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_10);
	App::Print(x1, 608, roman24, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(x2, 608, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(x1, 588, helvetica10, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_10);
	App::Print(x2, 588, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_10);
	App::Print(x1, 568, helvetica12, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12);
	App::Print(x2, 568, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12);
	App::Print(x1, 548, helvetica18, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_18);
	App::Print(x2, 548, sample, 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_18);
}

void DisplayManager::displayGameUI()
{	
	// level message
	char level[99];
	sprintf(level, "LEVEL: %d", m_levelManager->GetLevel());
	App::Print(100, 700, level, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	// life remaining
	char life[99];
	sprintf(life, "LIFE: %d", m_stateManager->GetLife());
	App::Print(470, 700, life, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	// display how much gold
	char gold[99];
	sprintf(gold, "GOLD: %d", m_stateManager->GetGold());
	App::Print(830, 700, gold, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print(40, 430, "SPACE - BUILD TOWER", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(40, 400, "ENTER - SPAWN ENEMY", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(40, 370, "BACKSPACE - PAUSE  ", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(30, 300, "Move the mouse on the", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);
	App::Print(30, 280, "grid to place tower", 1.0, 1.0, 1.0, GLUT_BITMAP_9_BY_15);

	PrintMousePosition();
}

void DisplayManager::PrintMousePosition()
{
	char position[99];
	float posX, posY;
	Index mouseIndex{ 0, 0 };

	App::GetMousePos(posX, posY);
	if (Toolbox::MouseInMap())
		mouseIndex = Toolbox::MouseToIndex({posX, posY});

	sprintf(position, "Index: [%d][%d] X: %.0f, Y: %.0f", mouseIndex.row, mouseIndex.column, posX, posY);

	App::Print(APP_VIRTUAL_WIDTH - 250, APP_VIRTUAL_HEIGHT - 760,
		position, 1.0, 1.0, 1.0, GLUT_BITMAP_8_BY_13);
}