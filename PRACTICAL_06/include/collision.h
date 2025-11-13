
#include "stdlib.h"
#include "Math.h"

typedef struct CircleStruct{
	
	int x;
	int y;
	int radius;
}CircleStruct;

typedef struct RectangleStruct{
	int x;
	int y;
	int width;
	int height;
}RectangleStruct;

bool circleToCircle(CircleStruct* a, CircleStruct* b)
{
	int distanceX = abs(a->x - b->x);
	int distanceY = abs(a->y - b->y);
	int distanceSqrt = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	int difference = a->radius + b->radius;
	
	if (distanceSqrt <= difference)
	{
		return true;
	}
	else
	{
		return false;
	}
}	

bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max); 
}

bool rectangleToRectangle(RectangleStruct* one, RectangleStruct* two)
{
	bool xOverlap = valueInRange(one->x, two->x, two->x + two->width) || valueInRange(two->x, one->x, one->x + one->width);
	
	bool yOverlap = valueInRange(one->y, two->y, two->y + two->height) || valueInRange(two->y, one->y, one->y + one->height);
	
	return xOverlap && yOverlap;
}