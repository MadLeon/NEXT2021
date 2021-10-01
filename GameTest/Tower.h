//------------------------------------------------------------------------
//ItemManager.h
//------------------------------------------------------------------------
#ifndef TOWER_H
#define TOWER_H
//------------------------------------------------------------------------
#include "Enemy.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Tower object
//------------------------------------------------------------------------
class Tower
{
	// Types of tower, for future expansion
	TowerType m_type;

	// Level of tower, for future expansion
	size_t m_level;

	// The index of the location
	Index m_index;

	// The center coordinate of the location
	Vec2 m_pos;

	// attack attributes
	float m_attackRange;
	float m_attackSpeed;
	float m_attackPower;

	// number of vertex at current level
	size_t m_numVertex;

	// The number of enemies already locked
	size_t m_numTargets;

	// Stores an array of pointers to locked enemies
	Enemy* m_target[MAX_NUM_ENEMY];

	// There is at least a locked enemy
	bool m_targetExist;

	// Current timestamp
	float m_currentTime;

	// Elapsed time since last shot
	float m_timeSinceLastShot;

	// Can shoot, which means not currently in attack CD
	// and there are enemies in the attack range
	bool m_canShoot;

	// Determine whether the attack has been carried out
	bool m_shot;

public:
	Tower::Tower() :
		m_level(1),
		m_type(TowerType::LASER),
		m_index({ 0, 0 }),
		m_attackRange(ATTACK_RANGE),
		m_attackSpeed(ATTACK_SPEED),
		m_attackPower(ATTACK_SPEED),
		m_currentTime(0),
		m_timeSinceLastShot(0),
		m_canShoot(false),
		m_shot(false),
		m_numTargets(0),
		m_targetExist(false),
		m_numVertex(MAX_TOWER_VERTEX - 4) {}

	// getters and setters
	void SetLocation(Index);
	void SetType(TowerType type) { m_type = type; }
	Index GetIndex() { return m_index; }

	//------------------------------------------------------------------------
	// Draw the defensive tower on the screen
	//------------------------------------------------------------------------
	void Draw();

	//------------------------------------------------------------------------
	// Connect the vertices of the defensive tower graphics
	//------------------------------------------------------------------------
	void ConnectVertex(Vec2 [], size_t);

	//------------------------------------------------------------------------
	// Look for enemies within 9 blocks centered on the defensive tower
	//------------------------------------------------------------------------
	void SearchEnemy(Enemy*[], size_t);

	//------------------------------------------------------------------------
	// Shoot at all enemies within range
	//------------------------------------------------------------------------
	void ShootEnemy(Enemy* [], size_t);

	//------------------------------------------------------------------------
	// Determine whether in attacking CD
	//------------------------------------------------------------------------
	void Load(float);

	//------------------------------------------------------------------------
	// Return whether there is target in the range
	//------------------------------------------------------------------------
	bool TargetLocked() { return m_targetExist; }
};

#endif // !TOWER_H
