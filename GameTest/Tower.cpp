//------------------------------------------------------------------------
//Tower.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
//------------------------------------------------------------------------
#include "Tower.h"
//------------------------------------------------------------------------

void Tower::SetLocation(Index index)
{
	m_index = index;
	m_pos = Toolbox::IndexToScreenCoordinate(index);
	m_canShoot = true;
}

void Tower::Draw()
{
	Vec2 towerShape[MAX_TOWER_VERTEX] =
	{ {-2,0}, {0,2}, {2,0}, {1,0}, {1,-2}, {-1,-2}, {-1,0}, {-1,-2.0/3}, {1,-2.0/3}, {1,-4.0/3}, {-1,-4.0/3} };

	GameMath::Scaling(towerShape, MAX_TOWER_VERTEX, TILE_LENGTH / 5);
	GameMath::Translation(towerShape, MAX_TOWER_VERTEX, Toolbox::IndexToScreenCoordinate(m_index));

	// connect vertex
	ConnectVertex(towerShape, MAX_TOWER_VERTEX);
}

void Tower::ConnectVertex(Vec2 vertex[], size_t numVertex)
{
	App::DrawLine(vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y, 1.0, 1.0, 1.0);
	App::DrawLine(vertex[1].x, vertex[1].y, vertex[2].x, vertex[2].y, 1.0, 1.0, 1.0);
	App::DrawLine(vertex[2].x, vertex[2].y, vertex[0].x, vertex[0].y, 1.0, 1.0, 1.0);

	for (size_t i = 3; i != m_numVertex - 1; ++i)
		App::DrawLine(vertex[i].x, vertex[i].y, vertex[i + 1].x, vertex[i + 1].y, 1.0, 1.0, 1.0);
}

void Tower::SearchEnemy(Enemy* enemies[], size_t num)
{
	// clear the attack list
	for (size_t i = 0; i != MAX_NUM_ENEMY; ++i)
	{
		m_target[i] = nullptr;
		m_numTargets = 0;
	}

	// find all enemies within range
	for (size_t i = 0; i != num; ++i)
		if (enemies[i] && enemies[i]->IsAlive() && GameMath::Distance(m_pos, enemies[i]->GetPos()) < m_attackRange)
			m_target[m_numTargets++] = enemies[i];

	m_targetExist = m_numTargets ? true : false;
}

void Tower::ShootEnemy(Enemy* enemies[], size_t num)
{
	if (m_canShoot && m_numTargets)
	{		
		// draw a line to each enemy - aoe attack 
		for (size_t i = 0; i != m_numTargets; ++i)
		{
			if (m_target[i])
			{
				App::DrawLine(
					m_pos.x, m_pos.y,
					m_target[i]->GetPos().x, m_target[i]->GetPos().y,
					0.0, 1.0, 1.0
				);
				// enemy's hp reduced
				m_target[i]->ReductHp();
			}
		}

		// set the weapon on cool down
		m_canShoot = false;
	}
}

void Tower::Load(float delta)
{
	if (m_shot) m_timeSinceLastShot = m_currentTime;

	m_currentTime += delta;

	if (m_currentTime - m_timeSinceLastShot > ATTACK_SPEED)
		m_canShoot = true;
}