#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <raylib.h>
#include "cute_c2.h"

// Collider types for NPCs
typedef enum
{
	CIRCLE, // Circle shape
	AABB,	// Axis-Aligned Bounding Box shape
	CAPSULE, // Capsule shape
	RAY      // Ray shape
} ColliderType;

// NPC (Non-Player Character) structure
typedef struct
{
	ColliderType type; // Type of the Collider
	Color color;	   // Color for rendering
	bool isColliding;  // Collision status

	// Manifold for finding incident normals
	c2Manifold manifold;

	union
	{
		c2Circle circle;   // center+radius
		c2AABB aabb;	   // min/max
		c2Capsule capsule; // a,b endpoints + r
		c2Ray ray;         // position, direction, distance
	} collider;

} NPC;

// Player structure
typedef struct
{
	c2Circle circle;   // Player represented as a circle
	Texture2D texture; // Player texture
	Color color;	   // Color for rendering
} PlayerCircle;

typedef struct 
{
	c2AABB aabb; // Player represented as an AABB
	Color color; // Color for rendering
}PlayerAABB;

typedef struct 
{
	c2Capsule capsule; // Player represented as a capsule
	Color color;       // Color for rendering
}PlayerCapsule;


#endif // GAME_OBJECT_H