//------------------------------------------------------------------------
//GameMath.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "GameMath.h"
//------------------------------------------------------------------------

void GameMath::Translation(Vec2 pts[], size_t length, Vec2 direction)
{
	Matrix3x3 m;

	m.SetIdentity();
	m[0][2] = direction.x;
	m[1][2] = direction.y;

	for (size_t i = 0; i != length; ++i)
		pts[i] *= m;
}

void GameMath::Scaling(Vec2 pts[], size_t length, float ratio)
{
	Matrix3x3 m;

	m.SetIdentity();
	m[0][0] *= ratio;
	m[1][1] *= ratio;

	for (size_t i = 0; i != length; ++i)
		pts[i] *= m;
}

float GameMath::Distance(Vec2 pt1, Vec2 pt2)
{
	return sqrtf(powf(pt2.x - pt1.x, 2) + powf(pt2.y - pt1.y, 2));
}

void GameMath::TranslatePoint(Vec2& point, Vec2 direction)
{
	Matrix3x3 m;

	m.SetIdentity();
	m[0][2] = direction.x;
	m[1][2] = direction.y;

	point *= m;
}

void GameMath::ScalePoint(Vec2& point, float ratio)
{
	Matrix3x3 m;

	m.SetIdentity();
	m[0][0] *= ratio;
	m[1][1] *= ratio;

	point *= m;
}
