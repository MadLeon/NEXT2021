//------------------------------------------------------------------------
//Toolbox.h
//------------------------------------------------------------------------
#ifndef TOOLBOX_TOOLBOX_H
#define TOOLBOX_TOOLBOX_H
//------------------------------------------------------------------------
#include "App/AppSettings.h"
//------------------------------------------------------------------------
#include "GameSettings.h"
#include "Types.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Contains gadget functions used in the game
//------------------------------------------------------------------------
namespace Toolbox
{
	//------------------------------------------------------------------------
	// Draw a quadrilateral according to the input coordinates
	//------------------------------------------------------------------------
	void DrawSquare(Vec2, Vec2, Vec2, Vec2);

	//------------------------------------------------------------------------
	// Draw a solid quadrilateral according to the input coordinates
	//------------------------------------------------------------------------
	void DrawSolidSquare(Vec2, Vec2, Vec2, Vec2);

	//------------------------------------------------------------------------
	// Convert the quadrilateral index to coordinates
	//------------------------------------------------------------------------
	void SquareIndexToCoordinate(size_t, size_t, Vec2[]);

	//------------------------------------------------------------------------
	// Convert a two-dimensional array coordinates to world coordinates
	//------------------------------------------------------------------------
	Vec2 IndexToScreenCoordinate(Index);

	//------------------------------------------------------------------------
	// Convert mouse coordinates to two-dimensional array coordinates
	//------------------------------------------------------------------------
	Index MouseToIndex(Vec2 mousePos);

	//------------------------------------------------------------------------
	// Determine whether the coordinates of the mouse are on the map
	//------------------------------------------------------------------------
	bool MouseInMap();
}

#endif // !TOOLBOX_TOOLBOX_H
