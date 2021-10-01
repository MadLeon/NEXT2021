//------------------------------------------------------------------------
//Toolbox.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "App/app.h"
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "Toolbox.h"
#include "GameMath.h"
#include "GameSettings.h"
//------------------------------------------------------------------------

namespace Toolbox
{
	void DrawSquare(Vec2 pt1, Vec2 pt2, Vec2 pt3, Vec2 pt4)
	{
		App::DrawLine(pt1.x, pt1.y, pt2.x, pt2.y, 1.0, 1.0, 1.0);
		App::DrawLine(pt2.x, pt2.y, pt3.x, pt3.y, 1.0, 1.0, 1.0);
		App::DrawLine(pt3.x, pt3.y, pt4.x, pt4.y, 1.0, 1.0, 1.0);
		App::DrawLine(pt4.x, pt4.y, pt1.x, pt1.y, 1.0, 1.0, 1.0);
	}

	void DrawSolidSquare(Vec2 pt1, Vec2 pt2, Vec2 pt3, Vec2 pt4)
	{
		size_t pixels = (size_t)GameMath::Distance(pt1, pt2) + 1;
		for (size_t i = 0; i <= pixels; ++i)
			App::DrawLine(pt1.x + i, pt1.y, pt4.x + i, pt4.y, 1.0, 1.0, 1.0);
	}

	void SquareIndexToCoordinate(size_t i, size_t j, Vec2 pt[])
	{

		pt[0] = { (float)i , 10 - (float)j };
		pt[1] = { (float)i + 1, 10 - (float)j };
		pt[2] = { (float)i + 1, 9 - (float)j };
		pt[3] = { (float)i, 9 - (float)j };
	}


	Vec2 IndexToScreenCoordinate(Index index)
	{
		Vec2 pos;

		pos.x = HORIZONTAL_MID_POINT - MAP_LENGTH / 2 + (index.column + 0.5) * TILE_LENGTH;
		pos.y = VERTICAL_MID_POINT - MAP_LENGTH / 2 + (9 - index.row + 0.5) * TILE_LENGTH;

		return pos;
	}

	Index MouseToIndex(Vec2 mousePos)
	{
		if (MouseInMap())
		{
			// translate coordinate to the origin
			GameMath::TranslatePoint(mousePos,
				{ -HORIZONTAL_MID_POINT + MAP_LENGTH / 2, -VERTICAL_MID_POINT + MAP_LENGTH / 2 });

			// scale back
			GameMath::ScalePoint(mousePos, 1 / (float)TILE_LENGTH);

			// convert float to integer
			mousePos.x = floorf(mousePos.x);
			mousePos.y = ceilf(mousePos.y);

			// convert coordinate to index
			return { 10 - (size_t)mousePos.y, (size_t)mousePos.x };
		}
		else
			return { 1, 1 };
	}

	bool MouseInMap()
	{
		Vec2 mousePos;
		App::GetMousePos(mousePos.x, mousePos.y);

		bool xIn = false, yIn = false;

		if (mousePos.x >= HORIZONTAL_MID_POINT - MAP_LENGTH / 2 &&
			mousePos.x <= HORIZONTAL_MID_POINT + MAP_LENGTH / 2)
			xIn = true;

		if (mousePos.y >= VERTICAL_MID_POINT - MAP_LENGTH / 2 &&
			mousePos.y <= VERTICAL_MID_POINT + MAP_LENGTH / 2)
			yIn = true;

		return xIn && yIn;
	}
}