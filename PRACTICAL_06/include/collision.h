
#include "stdlib.h"

typedef struct Circle{
	
	int x;
	int y;
	int radius;
}

typedef struct Rectangle{
	int x;
	int y;
	int a;
	int b;
}

bool circleToCircle(Circle* a, Circle* b)
{
	int distanceX = abs(a.x - b.x;)
	int distanceY = abs(a.y - b.y;)
	int difference = a.radius + b.radius;
	
	if (difference > distanceX || difference > distanceY)
	{
		return true;
	}
	
	return false;
}	


bool rectangleToRectangle(Rectangle* a, Rectangle* b)
{
	for(;b.x < b.x+b.a;b.x++)
	{
		if(b.x >= a.x && b.x <= a.x + a.a)
		{
			for(;b.y < b.y + b.b, b.y++)
			{
				if(b.y >= a.y && b.y <= a.y + a.b)
				{
					return true;
				}
			}
		}
	}
	
	return false;
}