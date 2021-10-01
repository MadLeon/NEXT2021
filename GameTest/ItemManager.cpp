//------------------------------------------------------------------------
//ItemManager.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "ItemManager.h"
//------------------------------------------------------------------------

ItemManager::ItemManager(StateManager* stateManager, LevelManager* levelManager) : 
	m_numEnemy(0),
	m_numEnemyDie(0),
	m_numTower(0)
{
	m_stateManager = stateManager;
	m_levelManager = levelManager;

	for (size_t i = 0; i != MAX_NUM_ENEMY; ++i)
		m_enemies[i] = nullptr;
	for (size_t i = 0; i != MAX_NUM_TOWER; ++i)
		m_army[i] = nullptr;
}

ItemManager::~ItemManager()
{
	m_stateManager = nullptr;
	m_levelManager = nullptr;

	for (size_t i = 0; i != m_numTower; ++i)
		delete m_army[i];
	for (size_t i = 0; i != m_numEnemy; ++i)
		delete m_enemies[i];
}

void ItemManager::BuildTower(TowerType type, Vec2 mousePos)
{
	bool canBuild = true;

	Index mouseIndex = Toolbox::MouseToIndex(mousePos);
	
	// if there is enough money && the location can build tower
	if (m_stateManager->GetGold() >= TOWER_COST &&
		m_levelManager->CheckPattern(mouseIndex) == 0)
	{
		// check the tile isn't occupied
		for (size_t i = 0; i != m_numTower; ++i)
		{
			if (m_army[i]->GetIndex().row == mouseIndex.row &&
				m_army[i]->GetIndex().column == mouseIndex.column)
			{
				canBuild = false;
				break;
			}
		}

		if (canBuild)
		{
			m_army[m_numTower] = new Tower;
			m_army[m_numTower]->SetLocation(mouseIndex);
			m_army[m_numTower]->SetType(type);
			m_numTower++;
			m_stateManager->GoldReduction(TOWER_COST);
		}		
	}
}

void ItemManager::CreateEnemy(size_t i, size_t level)
{
	m_enemies[i] = new Enemy(m_levelManager, m_stateManager, level);
	m_numEnemy++;
}

void ItemManager::Draw()
{	
	// draw tower
	for (size_t i = 0; i != m_numTower; ++i)
		m_army[i]->Draw();

	// draw enemies
	for (size_t i = 0; i != m_numEnemy; ++i)
	{
		// enemy reaches the destination
		if (m_enemies[i] && !m_enemies[i]->IsAlive())
		{
			delete m_enemies[i];
			m_enemies[i] = nullptr;
			m_numEnemyDie++;
		}

		if (m_enemies[i])
			m_enemies[i]->Draw();
	}

	// draw bullet/laser
	if (m_numEnemy)
		for (size_t i = 0; i != m_numTower; ++i)
			if (m_army[i]->TargetLocked())
				m_army[i]->ShootEnemy(m_enemies, m_numEnemy);
}

void ItemManager::Update(float deltaTime)
{
	// enemy update
	for (size_t i = 0; i != m_numEnemy; ++i)
		if (m_enemies[i])
			m_enemies[i]->Update(deltaTime);

	// tower update
	if (m_numEnemy)
		for (size_t i = 0; i != m_numTower; ++i)
		{
			m_army[i]->SearchEnemy(m_enemies, m_numEnemy);
			m_army[i]->Load(deltaTime);
		}

	if (m_numEnemyDie == MAX_NUM_ENEMY)
	{
		if (m_levelManager->GetLevel() == 3)
			m_levelManager->SetClearOn();
		else
		{
			m_levelManager->LevelChangeOn();
			m_numEnemyDie = 0;
		}
	}
}

void ItemManager::reset()
{
	for (size_t i = 0; i != m_numTower; ++i)
		delete m_army[i];
	for (size_t i = 0; i != m_numEnemy; ++i)
		delete m_enemies[i];

	m_numTower = 0;
	m_numEnemy = 0;
	m_numEnemyDie = 0;
}