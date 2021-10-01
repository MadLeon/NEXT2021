//------------------------------------------------------------------------
//EnemySpawner.h
//------------------------------------------------------------------------
#ifndef ENEMYSPAWNER_H
#define ENEMYSPWNAER_H
//------------------------------------------------------------------------
class ItemManager;
class LevelManager;

class EnemySpawner
{
	ItemManager* m_itemManager;
	LevelManager* m_levelManager;

	// Number of enemies spawned
	size_t m_spawned;

	// The level of the born enemy
	size_t m_enemyLevel;

	// The number of enemies that need to be summoned 
	// before the first spawn speed increase
	size_t m_initialNumber;

	// According to map level, the correction value of the enemy's birth level
	size_t m_levelCorrection;

	// Determine if it is active, 
	// turn off after spawning the maximum number of enemies
	bool m_active;

	// Tell whether it can spawn a new enemy, 
	// turn off when in spawning CD
	bool m_canSpawn;

	// The time interval between two spawns
	float m_timeBetween;

	// The time elapsed since the last spawn
	float m_timeSinceLastSpawn;

	// Current timestamp
	float m_currentTime;

public:
	EnemySpawner(ItemManager*, LevelManager*);
	~EnemySpawner();

	// getters and setters
	size_t GetSpawned() { return m_spawned; }
	void SetSpeed(float speed) { m_timeBetween = speed; }
	bool IsActive() { return m_active; }

	//------------------------------------------------------------------------
	// Start spawning
	// Usually starts after the player presses the space
	//------------------------------------------------------------------------	
	void Begin();

	//------------------------------------------------------------------------
	// Update function, usually for evaluation and spawning action
	//------------------------------------------------------------------------
	void Update(float);

	//------------------------------------------------------------------------
	// Spawn a new enemy
	//------------------------------------------------------------------------
	void Spawn();

	//------------------------------------------------------------------------
	// Set the level of new born enemies 
	// based on the number of enemies already summoned
	//------------------------------------------------------------------------
	void SetEnemyLevel();

	//------------------------------------------------------------------------
	// Increase spawning speed
	// based on the number of enemies already summoned
	//------------------------------------------------------------------------
	void SpeedRefresh();

	//------------------------------------------------------------------------
	// Reset this object
	//------------------------------------------------------------------------
	void reset();
};

#endif // !ENEMYSPAWNER_H
