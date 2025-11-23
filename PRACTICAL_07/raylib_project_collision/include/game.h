#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "game_object.h"

// Game data structure
typedef struct GameData
{
	PlayerCircle playerCircle;		// Player circle
	PlayerAABB playerAABB;
	PlayerCapsule playerCapsule;
	NPC npcs[NUM_NPCS]; // Array of NPCs (Non-Player Characters / could also be obstacles)

	int points;			  // Game Points
	int collisionCounter; // Counter for collisions
	char message[200];	  // Message buffer for collision status
	bool drawCrc;
	bool drawRect;
	bool drawCps;
} GameData;

// Function prototypes
void InitGame(GameData *data);
void UpdateGame(GameData *data);
void DrawGame(const GameData *data);
void CloseGame(GameData *data);

#endif // GAME_H