//------------------------------------------------------------------------
//ItemManager.h
//------------------------------------------------------------------------
#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H
//------------------------------------------------------------------------
#include "Tower.h"
#include "Enemy.h"
#include "StateManager.h"
#include "LevelManager.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Responsible for creating and destroying defensive towers and enemy objects
//------------------------------------------------------------------------
class ItemManager
{
	// number of towers that have been built
	size_t m_numTower;

	// total number of enemy summoned
	size_t m_numEnemy;

	// Number of dead enemies
	size_t m_numEnemyDie;

	// Storage location of towers
	Tower* m_army[MAX_NUM_TOWER];

	// Storage location of enemies
	Enemy* m_enemies[MAX_NUM_ENEMY];

	StateManager* m_stateManager;
	LevelManager* m_levelManager;

public:
	ItemManager(StateManager*, LevelManager*);
	~ItemManager();

	// getters
	size_t GetNumTower() { return m_numTower; }
	size_t GetNumEnemy() { return m_numEnemy; }

	//------------------------------------------------------------------------
	// Build a new defensive tower at the mouse location, 
	// and check if it can be built before building
	//------------------------------------------------------------------------
	void BuildTower(TowerType, Vec2);

	//------------------------------------------------------------------------
	// Make a new enemy object
	// Always called by EnemySpawner
	//------------------------------------------------------------------------
	void CreateEnemy(size_t, size_t);

	//------------------------------------------------------------------------
	// Display all currently existing towers and enemies
	//------------------------------------------------------------------------
	void Draw();

	//------------------------------------------------------------------------
	// Call the update function of all objects
	//------------------------------------------------------------------------
	void Update(float);

	//------------------------------------------------------------------------
	// Reset this object
	//------------------------------------------------------------------------
	void reset();
};


#endif // !ITEMMANAGER_H