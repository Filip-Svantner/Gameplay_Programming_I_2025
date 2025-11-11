
#include "stdlib.h"

typedef struct CircleStruct{
	
	int x;
	int y;
	int radius;
}CircleStruct;

typedef struct RectangleStruct{
	int x;
	int y;
	int a;
	int b;
}RectangleStruct;

bool circleToCircle(CircleStruct* a, CircleStruct* b)
{
	int distanceX = abs(a->x - b->x);
	int distanceY = abs(a->y - b->y);
	int difference = a->radius + b->radius;
	
	if (difference > distanceX || difference > distanceY)
	{
		return true;
	}
	
	return false;
}	


bool rectangleToRectangle(RectangleStruct* one, RectangleStruct* two)
{
	for(;two->x < two->x + two->a ;two->x++)
	{
		if(two->x >= one->x && two->x <= one->x + one->a)
		{
			for(;two->y < two->y + two->b; two->y++)
			{
				if(two->y >= one->y && two->y <= one->y + one->b)
				{
					return true;
				}
			}
		}
	}
	
	return false;
}