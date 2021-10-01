//------------------------------------------------------------------------
//Level.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "LevelManager.h"
//------------------------------------------------------------------------


void LevelManager::DrawMap()
{
	switch (m_level)
	{
	case 1:
		DrawLevelOne();
		break;
	case 2:
		DrawLevelTwo();
		break;
	case 3:
		DrawLevelThree();
		break;
	default:
		break;
	}
}

void LevelManager::DrawLevelOne()
{
	VisualizePattern(m_pattern1);	
}

void LevelManager::DrawLevelTwo()
{
	VisualizePattern(m_pattern2);
}

void LevelManager::DrawLevelThree()
{
	VisualizePattern(m_pattern3);
}

void LevelManager::VisualizePattern(size_t pattern[NUM_TILES][NUM_TILES])
{
	Vec2 pt[NUM_VERTEX];

	for (size_t j = 0; j != NUM_TILES; ++j)
	{
		for (size_t i = 0; i != NUM_TILES; ++i)
		{
			// convert indexes to coordinates
			Toolbox::SquareIndexToCoordinate(i, j, pt);

			// scale
			GameMath::Scaling(pt, NUM_VERTEX, TILE_LENGTH);

			// translate coordinates to the center of the window
			GameMath::Translation(pt, NUM_VERTEX, 
				{ HORIZONTAL_MID_POINT - MAP_LENGTH / 2, VERTICAL_MID_POINT - MAP_LENGTH / 2 });

			if (pattern[j][i] == 0)
			{
				// draw a square
				Toolbox::DrawSquare(pt[0], pt[1], pt[2], pt[3]);
			}
		}
	}
}

size_t LevelManager::CheckPattern(Index i)
{
	if (m_level == 1) return m_pattern1[i.row][i.column];
	if (m_level == 2) return m_pattern2[i.row][i.column];
	if (m_level == 3) return m_pattern3[i.row][i.column];
	return 1;
}


