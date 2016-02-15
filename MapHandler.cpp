#include <iostream>
#include "MapHandler.h"

using namespace std;

Map::Map()
{
	//Rectangle R1(20, 30);
}

void Map::initMap(void)
{
	for (uint8 i = 0; i < MAP_ROW; i++)
	{
		for (uint8 j = 0; j < MAP_COLUMN; j++)
		{
			room[i][j] = UNCOVERED;
		}
	}
}

#ifdef RECTANGLE
void Map::AddRectangle(Rectangle rect, RobotPos* position)
{
	Map::room;
	RectSize size;
	rect.getRectSize(&size);
	uint8 x_offset = size.X_Dist / 2;
	uint8 y_offset = size.Y_Dist / 2;

	for (uint8 i = 0; i < size.Y_Dist; i++)
	{
		for (uint8 j = 0; j < size.X_Dist; j++)
		{
			if ((Map::room[i][j] != CLEANED) && (Map::room[i][j] != BUSY))
			//Map::room[x_offset - i][y_offset - j] = EMPTY;
			Map::room[i][j] = EMPTY;
			else if (Map::room[i][j] == CLEANED)
			{

			}
			else if (Map::room[i][j] != BUSY)
			{

			}
		}
	}
}
#endif

void Map::addRobotOnMap(RobotPos robPosition)
{
	Map::room[robPosition.Y_pos][robPosition.X_pos] = ROBOT;
}

void Map::addPointOnMap(Point newpoint, Robot rob, Heading heading)
{
	PointPos PointPosition;
	RobotPos RobPosition;
	uint8 EmptyDistance;
	uint8 StartSwipe;
	PointPosition = newpoint.getPointPos();
	room[PointPosition.Y_Row][PointPosition.X_Column] = BUSY;

	/*clearing area between robot and obstical*/
	RobPosition = rob.GetRobotPosition();

	if ((heading == NORTH) || (heading == SOUTH))
	{
		if ((RobPosition.X_pos - PointPosition.X_Column) < 0)
		{
			StartSwipe = RobPosition.X_pos + 1;
			EmptyDistance = (((RobPosition.X_pos - PointPosition.X_Column) * -1)) + RobPosition.X_pos;
		}
		else
		{
			StartSwipe = PointPosition.X_Column + 1;
			EmptyDistance = ((RobPosition.X_pos - PointPosition.X_Column)) + PointPosition.X_Column;
		}

		for (uint8 i = StartSwipe; i < EmptyDistance; i++)
		{
			if ((room[PointPosition.Y_Row][i] != CLEANED) && (room[PointPosition.Y_Row][i] != BUSY))
			{
				room[PointPosition.Y_Row][i] = EMPTY;
			}
		}
	}
	else if ((heading == WEST) || (heading == EAST))
	{
		if ((RobPosition.Y_pos - PointPosition.Y_Row) < 0)
		{
			StartSwipe = RobPosition.Y_pos + 1;
			EmptyDistance = (((RobPosition.Y_pos - PointPosition.Y_Row) * -1)) + RobPosition.Y_pos;
		}
		else
		{
			StartSwipe = PointPosition.Y_Row + 1;
			EmptyDistance = ((RobPosition.Y_pos - PointPosition.Y_Row)) + PointPosition.Y_Row;
		}

		for (uint8 i = StartSwipe; i < EmptyDistance; i++)
		{
			if ((room[i][PointPosition.X_Column] != CLEANED) && (room[i][PointPosition.X_Column] != BUSY))
			{
				room[i][PointPosition.X_Column] = EMPTY;
			}
		}
	}
}

void Map::UpdateRobotPosition(Robot rob)
{
	for (uint8 i = 0; i < MAP_ROW; i++)
	{
		for (uint8 j = 0; j < MAP_COLUMN; j++)
		{
			if ((rob.GetRobotPosition().X_pos == i) && (rob.GetRobotPosition().Y_pos == j))
			{
				room[j][i] = ROBOT;
			}
			else if (room[j][i] == ROBOT)
			{
				room[j][i] = CLEANED;
			}
		}
	}
}

void Map::MergePointsOnMap(PointPos newPointPos, PointPos oldPointPos)
{
	
	room[oldPointPos.Y_Row][oldPointPos.X_Column] = UNCOVERED;
	room[newPointPos.Y_Row][newPointPos.X_Column] = BUSY;
}
