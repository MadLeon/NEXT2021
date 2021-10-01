//------------------------------------------------------------------------
//Enemy.h
//------------------------------------------------------------------------
#ifndef ENEMY_H
#define ENEMY_H
//------------------------------------------------------------------------
#include "LevelManager.h"
#include "StateManager.h"

//------------------------------------------------------------------------
// Enemy Object
//------------------------------------------------------------------------
class Enemy
{
	// current HP
	int m_hp;

	// HP when the monster spawns / total HP
	int m_originalHp;

	size_t m_level;

	// movement speed, number of pixels per frame
	float m_speed;	

	// used to tell whether the enemy is alive
	bool m_alive;

	// current coordinate
	Vec2 m_pos;

	// last coordinate before movement
	Vec2 m_lastPos;

	// the coordinates to be moved to
	Vec2 m_nextPos;

	// map's end position
	Vec2 m_endPos;

	// direction of movement
	Direction m_direction;

	// the current index in the two-dimensional array
	Index m_index;

	// last index before movement
	Index m_lastIndex;

	// the next index to be moved to
	Index m_nextIndex;

	// end index
	Index m_endIndex;

	// the coordinates of the enemy shape in the self coordinate system
	Vec2 m_pattern[NUM_ENEMY_VERTEX]
	{ 
		{-2,1},{0,2},{2,1},{0,1},
		{0,-1},{-2,-2},{2,-2},
		{0,0},{-2,-0.5},{2,-0.5} 
	};

	LevelManager* m_levelManager;
	StateManager* m_stateManager;

public:
	Enemy(LevelManager*, StateManager*, size_t);

	// getters and setters
	size_t GetHp() { return m_hp; }
	void SetHp(size_t hp) { m_hp = hp; }
	float GetSpeed() { return m_speed; }
	Vec2 GetPos() { return m_pos; }

	bool IsAlive() { return m_alive; }

	//------------------------------------------------------------------------
	// Monster HP after deducting the attack power of the defensive tower
	//------------------------------------------------------------------------
	void ReductHp() { m_hp -= ATTACK_POWER; }

	//------------------------------------------------------------------------
	// 2D transform enemy image coordinates to world coordinates
	//------------------------------------------------------------------------
	void Build();

	//------------------------------------------------------------------------
	// Draw the enemy in different colors according to its hp left
	//------------------------------------------------------------------------
	void Draw();

	//------------------------------------------------------------------------
	// Connect all vertex of the enemy shape
	//------------------------------------------------------------------------
	void ConnectVertex(float, float, float);

	//------------------------------------------------------------------------
	// Find the coordinates of the next movable point 
	// from the two-dimensional array of the map 
	// according to its 2D array index
	//------------------------------------------------------------------------
	void FindNextPos();
	void Update(float deltaTime);
};

#endif // !ENEMY_H
