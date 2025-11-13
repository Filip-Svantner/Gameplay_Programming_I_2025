
#include "stdlib.h"
#include "Math.h"

typedef struct CircleStruct{ //struct for Circle
	
	int x;
	int y;
	int radius;
}CircleStruct;

typedef struct RectangleStruct{ //struct for Rectangle 
	int x;
	int y;
	int width;
	int height;
}RectangleStruct;

bool circleToCircle(CircleStruct* a, CircleStruct* b) //Collision check through radius and distance
{
	int distanceX = abs(a->x - b->x); //distance on x axis
	int distanceY = abs(a->y - b->y); // distance on y axis
	int distanceSqrt = sqrt((distanceX * distanceX) + (distanceY * distanceY)); // straight line distance
	int difference = a->radius + b->radius; // sum of radiuses
	
	if (distanceSqrt <= difference) 
	{
		return true;
	}
	else
	{
		return false;
	}
}	

bool valueInRange(int value, int min, int max) // checks if the value is in range
{
	return (value >= min) && (value <= max); 
}

bool rectangleToRectangle(RectangleStruct* one, RectangleStruct* two) // checks if the x and y points of one square fit the other square and vice versa
{
	bool xOverlap = valueInRange(one->x, two->x, two->x + two->width) || valueInRange(two->x, one->x, one->x + one->width); // overlap on x axis
	
	bool yOverlap = valueInRange(one->y, two->y, two->y + two->height) || valueInRange(two->y, one->y, one->y + one->height); // overlap on y axis
	
	return xOverlap && yOverlap;
}