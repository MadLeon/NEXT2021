#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#define GAME_TITLE				"M Y    L I T T L E    T O W E R"
#define SUB_TITLE				"PRESS ENTER TO START"

// title's horizontal length
#define	TITLE_LENGTH			315
#define SUB_TITLE_LENGTH		147

// The center coordinate of the screen
#define HORIZONTAL_MID_POINT	512
#define VERTICAL_MID_POINT		384

#define MAP_LENGTH				500
#define TILE_LENGTH				50

// Player resources at the beginning stage
#define INITIAL_GOLD			100
#define INITIAL_LIFE			3

// Total number of levels
#define NUM_LEVELS				3

// The value range of each dimension of the two-dimensional array
#define NUM_TILES				10

// The number of vertices of the map
#define NUM_VERTEX				4

// The number of vertices of the enemy image
#define NUM_ENEMY_VERTEX		10

// The number of vertices of the tower image
#define MAX_TOWER_VERTEX		11

//------------------------------------------------------
// Tower statics
//------------------------------------------------------

// Tower construction cost
#define TOWER_COST				50

// Maximum number of defensive towers built
#define MAX_NUM_TOWER			99

// Defensive tower's attack statics
#define ATTACK_RANGE			100.0	// radius
#define ATTACK_SPEED			1	// per second
#define ATTACK_POWER			1	// hit points

//------------------------------------------------------
// Enemy statics
//------------------------------------------------------

// Maximum number of enemy to spawn
#define MAX_NUM_ENEMY			99

// movement speed
#define ENEMY_SPEED				2

// Reward for killing an enemy
#define ENEMY_REWARD			4

#endif // !GAMESETTINS_H
