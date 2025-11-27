#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

#include "player.h"

// Forward declaration of the Mediator struct
typedef struct Mediator Mediator;

// Define the Command enum combining different commands into bit flags
// Movement could be defined as just MOVE with direction (for simplicity, each direction is separate)

typedef enum
{
	NONE		 	= 0,		// No command
	MOVE_UP 		= 1 << 0,	// Binary: 0000001
	MOVE_DOWN 		= 1 << 1,	// Binary: 0000010
	MOVE_LEFT 		= 1 << 2,	// Binary: 0000100
	MOVE_RIGHT 		= 1 << 3,	// Binary: 0001000
	JUMP 			= 1 << 4,	// Binary: 0010000
	FIRE 			= 1 << 5,	// Binary: 0100000
	UNDO            = 1 << 6,   // Binary: 1000000
	COUNT			= 7 // Total number of commands
} Command;

// Function to execute a command
void ExecuteCommand(Command command, Player *player, float deltaTime);

// Function to show active command bits (for debugging)
void GetCommandBits(Command cmd, char *buffer);

// Check if a specific command is active
bool IsCommandActive(Command command, Command filter);

#endif // COMMAND_H
