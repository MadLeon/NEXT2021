//------------------------------------------------------------------------
//EnemySpawner.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "ItemManager.h"
#include "EnemySpawner.h"
#include "LevelManager.h"
//------------------------------------------------------------------------

EnemySpawner::EnemySpawner(ItemManager* itemManager, LevelManager* levelManager) : 
	m_spawned(0), 
	m_enemyLevel(0),
	m_levelCorrection(1),
	m_initialNumber(TOWER_COST / ENEMY_REWARD + 1),
	m_active(false), 
	m_canSpawn(true),
	m_currentTime(0),
	m_timeSinceLastSpawn(0)
{
	m_levelManager = levelManager;
	m_itemManager = itemManager;
}

EnemySpawner::~EnemySpawner()
{
	m_itemManager = nullptr;
}

void EnemySpawner::Begin()
{
	m_active = true;
}

void EnemySpawner::Update(float deltaTime)
{
	m_currentTime += deltaTime;

	if (m_active && m_canSpawn)
	{
		m_timeSinceLastSpawn = m_currentTime;
		Spawn();
		m_canSpawn = false;
	}

	if (m_spawned == MAX_NUM_ENEMY)
		m_active = false;

	if (m_currentTime - m_timeSinceLastSpawn > m_timeBetween && m_active)
		m_canSpawn = true;

	

	// As the number of summoned monsters increases
	// increase the spawning speed
	SpeedRefresh();
}

void EnemySpawner::Spawn()
{
	// As the number of summoned monsters increases
	// increase new monsters' level
	SetEnemyLevel();

	m_itemManager->CreateEnemy(m_spawned++, m_enemyLevel);
}

void EnemySpawner::SetEnemyLevel()
{
	m_enemyLevel = m_spawned <= m_initialNumber ? m_levelCorrection
		: m_spawned <= m_initialNumber * 2 ? 1 + m_levelCorrection
		: m_spawned <= m_initialNumber * 4 ? 2 + m_levelCorrection
		: m_spawned <= m_initialNumber * 6 ? 3 + m_levelCorrection
		: m_spawned <= m_initialNumber * 8 ? 4 + m_levelCorrection
		: 5 + m_levelCorrection;
}

void EnemySpawner::SpeedRefresh()
{
	m_timeBetween = m_spawned <= 5 ? 2000
		: m_spawned <= 10 ? 1000
		: m_spawned <= 20 ? 500
		: m_spawned <= 40 ? 300
		: m_spawned <= 60 ? 200
		: 100;
}

void EnemySpawner::reset()
{
	m_spawned = 0;
	m_active = false;
	m_canSpawn = true;
	m_levelCorrection = m_levelManager->GetLevel() * 2 ;
}