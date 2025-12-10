#ifndef EVENTS_H
#define EVENTS_H

// Define an enumeration for different event types
typedef enum
{
	EVENT_NONE, // Represents no event or an idle state where nothing happens.

	// Movement Events:
	EVENT_MOVE, // A general move event for when the player is moving in any direction, used as a catch-all for movement.

	// Environmental/State Events:
	// EVENT_FLOOR_LAND, // Represents the player landing on the floor after a jump or fall (e.g., gravity pulling the player down).

	// Combat Events:
	EVENT_ATTACK, // Represents a basic attack event (e.g., player character performing a melee or ranged attack).
	// EVENT_ATTACK_SPECIAL, // Represents performing a special or charged attack (e.g., a powerful or combo attack).
	EVENT_DEFEND, // Represents the player character activating a defense action (e.g., blocking, shielding).

	// Life Cycle Events:
	EVENT_DIE,	   // Represents the player character dying (e.g., health reaching zero or being defeated by an enemy).
	EVENT_RESPAWN, // Represents the player respawning after death (e.g., after a timeout, or at a checkpoint).
	// EVENT_HURT,    // Represents the player character taking damage (e.g., from enemies, traps, or environmental hazards).
	// EVENT_HEAL,    // Represents the player character receiving healing (e.g., health items or regenerative effects).

	// Collision Events:
	EVENT_COLLISION_START, // Represents the start of a collision (e.g., player colliding with a wall, enemy, or object).
	EVENT_COLLISION_END,   // Represents the end of a collision (e.g., player moving away from a colliding object or enemy).

	EVENT_SUPER_POWER,

	EVENT_COUNT // Represents the total number of events (for counting purposes, typically used for array size).
} Event;		// Define 'Event' as the type of the enum

#endif // EVENTS_H
