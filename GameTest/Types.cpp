//------------------------------------------------------------------------
//Types.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Types.h"

Matrix3x3::Matrix3x3()
{
	for (size_t i = 0; i != 3; ++i)
		for (size_t j = 0; j != 3; ++j)
			value[i][j] = 0;
}

void Matrix3x3::SetIdentity()
{
	for (size_t i = 0; i != 3; ++i)
		for (size_t j = 0; j != 3; ++j)
			if (i == j)
				value[i][j] = 1;
}

Vec2 Vec2::operator+(Vec2 vec)
{	
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator+=(Vec2 vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vec2 Vec2::operator-(Vec2 vec)
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator-=(Vec2 vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vec2 Vec2::operator*(Matrix3x3 m)
{
	return Vec2(m[0][0] * x + m[0][1] * y + m[0][2],
		m[1][0] * x + m[1][1] * y + m[1][2]);
}

Vec2 Vec2::operator*=(Matrix3x3 m)
{
	x = m[0][0] * x + m[0][1] * y + m[0][2];
	y = m[1][0] * x + m[1][1] * y + m[1][2];

	return *this;
}

Vec2 Vec2::operator==(Vec2 vec)
{
	return ((x == vec.x) && (y == vec.y));
}