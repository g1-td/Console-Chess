#pragma once
struct Coords
{
	int startX = 0, startY = 0, exitX = 0, exitY = 0;

	static Coords copyCoords(const Coords& original, Coords& copy)
	{
		copy.startX = original.startX;
		copy.startY = original.startY;
		copy.exitX = original.exitX;
		copy.exitY = original.exitY;

		return copy;
	}

	static bool cmpCoords(Coords a, Coords b)
	{
		return a.startX == b.startX &&
			a.startY == b.startY &&
			a.exitX == b.exitX &&
			a.exitY == b.exitY;
	}
};