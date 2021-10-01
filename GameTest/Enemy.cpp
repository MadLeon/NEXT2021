//------------------------------------------------------------------------
//Enemy.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "Enemy.h"
//------------------------------------------------------------------------

Enemy::Enemy(LevelManager* levelManager, StateManager* stateManager, size_t level) :
	m_level(level),
	m_speed(ENEMY_SPEED),
	m_alive(true),
	m_index({ 1,0 }),
	m_lastIndex({ 1 ,0 }),
	m_endIndex({ 8, 9 }),
	m_direction(Direction::RIGHT)
{
	m_hp = 100 * level;
	m_originalHp = m_hp;
	m_pos = Toolbox::IndexToScreenCoordinate(m_index);
	m_endPos = Toolbox::IndexToScreenCoordinate(m_endIndex);
	m_lastPos = m_pos;
	m_levelManager = levelManager;
	m_stateManager = stateManager;
	m_nextIndex = m_index;
	FindNextPos();
	Build();
}

void Enemy::Build()
{
	GameMath::Scaling(m_pattern, NUM_ENEMY_VERTEX, TILE_LENGTH / 8);
	GameMath::Translation(m_pattern, NUM_ENEMY_VERTEX, m_pos);
}

void Enemy::Draw()
{
	if (m_hp <= m_originalHp / 5)
		ConnectVertex(1.0, 0.0, 0.0);
	else if (m_hp <= m_originalHp / 2.5)
		ConnectVertex(1.0, 1.0, 0.0);	
	else
		ConnectVertex(1.0, 1.0, 1.0);
	GameMath::Translation(m_pattern, NUM_ENEMY_VERTEX, m_pos - m_lastPos);
}

void Enemy::ConnectVertex(float r, float g, float b)
{
	App::DrawLine(m_pattern[0].x, m_pattern[0].y, m_pattern[1].x, m_pattern[1].y, r, g, b);
	App::DrawLine(m_pattern[1].x, m_pattern[1].y, m_pattern[2].x, m_pattern[2].y, r, g, b);
	App::DrawLine(m_pattern[2].x, m_pattern[2].y, m_pattern[0].x, m_pattern[0].y, r, g, b);
	App::DrawLine(m_pattern[3].x, m_pattern[3].y, m_pattern[4].x, m_pattern[4].y, r, g, b);
	App::DrawLine(m_pattern[4].x, m_pattern[4].y, m_pattern[5].x, m_pattern[5].y, r, g, b);
	App::DrawLine(m_pattern[4].x, m_pattern[4].y, m_pattern[6].x, m_pattern[6].y, r, g, b);
	App::DrawLine(m_pattern[4].x, m_pattern[4].y, m_pattern[6].x, m_pattern[6].y, r, g, b);
	App::DrawLine(m_pattern[7].x, m_pattern[7].y, m_pattern[8].x, m_pattern[8].y, r, g, b);
	App::DrawLine(m_pattern[7].x, m_pattern[7].y, m_pattern[9].x, m_pattern[9].y, r, g, b);
}

void Enemy::FindNextPos()
{
	// find next movable grid and direction
	// the next grid cannot have the same index with the former one 
	if (m_nextIndex.column + 1 != m_lastIndex.column && 
		m_levelManager->CheckPattern({ m_nextIndex.row, m_nextIndex.column + 1 }))
	{
		m_nextIndex.column++;
		m_direction = Direction::RIGHT;
	}
	else if (m_nextIndex.row + 1 != m_lastIndex.row && 
		m_levelManager->CheckPattern({ m_nextIndex.row + 1, m_nextIndex.column }))
	{
		m_nextIndex.row++;
		m_direction = Direction::DOWN;
	}
	else if (m_nextIndex.column - 1 != m_lastIndex.column &&
		m_levelManager->CheckPattern({ m_nextIndex.row, m_nextIndex.column - 1 }))
	{
		m_nextIndex.column--;
		m_direction = Direction::LEFT;
	}
	else
	{
		m_nextIndex.row--;
		m_direction = Direction::UP;
	}
	// convert next index to next coordinate
	m_nextPos = Toolbox::IndexToScreenCoordinate(m_nextIndex);
}

void Enemy::Update(float deltaTime)
{
	if (m_hp <= 0)
	{
		m_alive = false;
		m_stateManager->GoldIncrease(ENEMY_REWARD);
	}
	// enemy arrived the end position
	if (m_pos.x == m_endPos.x && m_pos.y == m_endPos.y)
	{
		// play sound effect
		App::PlaySoundW("TestData/Test.wav");

		// mark itself dead
		m_alive = false;

		// player's hp - 1
		m_stateManager->LifeReduction();

		return;
	}

	if (m_alive)
	{
		// arrived at the predetermined location
		if (m_pos.x == m_nextPos.x && m_pos.y == m_nextPos.y)
		{
			// update index
			m_lastIndex = m_index;
			m_index = m_nextIndex;

			FindNextPos();
		}

		// save current coordinate in history
		m_lastPos = m_pos;

		// update coordinate based on direction
		switch (m_direction)
		{
		case Direction::UP:
			m_pos.y += m_speed;
			break;
		case Direction::RIGHT:
			m_pos.x += m_speed;
			break;
		case Direction::LEFT:
			m_pos.x -= m_speed;
			break;
		case Direction::DOWN:
			m_pos.y -= m_speed;
			break;
		default:
			break;
		}
	}
}