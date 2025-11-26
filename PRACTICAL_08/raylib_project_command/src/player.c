#include <raylib.h>

#include <stdio.h>
#include <math.h>

#include "player.h"

PlayerState *createPlayerState(Player *t_player)
{
	PlayerState *state = (PlayerState *)malloc(sizeof(PlayerState));
	state->x = t_player->x;
	state->y = t_player->y;
	state->color = t_player->color;
	state->health = t_player->health;
	return state;
}
Memento *createMemento(PlayerState *t_pState)
{
	Memento *memento = (Memento *)malloc(sizeof(Memento));
	memento->state = t_pState;
	return memento;
}
PlayerState *getPlayerState(Memento *t_memento)
{
	return t_memento->state;
}

// Keep player in screen bounds
void ClampPlayerOnScreen(Player *player)
{
	if (player->x < player->r)
		player->x = player->r;
	if (player->x > SCREEN_WIDTH - player->r)
		player->x = SCREEN_WIDTH - player->r;
	if (player->y < player->r)
		player->y = player->r;
	if (player->y > SCREEN_HEIGHT - player->r)
		player->y = SCREEN_HEIGHT - player->r;
}

// Player Idle Behaviour
void Idle(Player *player, float deltaTime)
{
	// Simple breathing effect by changing radius over time
	// Idle animation
	player->breathTimer += deltaTime;
	player->color = GREEN; // Change color to indicate idle or default color
	float wave = sinf(player->breathTimer * 3.0f);
	float scale = 1.0f + (wave * 0.05f);

	player->r = (int)(DEFAULT_PLAYER_RADIUS * scale);
}

// Move player up
void MoveUp(Player *player)
{
	savePlayerState(player);
	// Simple move up
	player->y -= 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved up to (%d, %d)\n", player->x, player->y);
}

// Move up and Fire
void MoveUpFire(Player *player)
{
	savePlayerState(player);
	// Move up and fire
	player->y -= 1;
	player->x -= 3; // Recoil effect
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("\n\nPlayer moved up to (%d, %d) and FIRED\n\n", player->x, player->y);
}

// Move player down
void MoveDown(Player *player)
{
	savePlayerState(player);
	// Simple move down
	player->y += 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved down to (%d, %d)\n", player->x, player->y);
}

// Move player left
void MoveLeft(Player *player)
{
	savePlayerState(player);
	// Simple move left
	player->x -= 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved left to (%d, %d)\n", player->x, player->y);
}

// Move player right
void MoveRight(Player *player)
{
	savePlayerState(player);
	// Simple move right
	player->x += 1;
	player->color = GREEN; // Change color to default color
	ClampPlayerOnScreen(player);
	printf("Player moved right to (%d, %d)\n", player->x, player->y);
}

// Player fires
void Fire(Player *player)
{
	savePlayerState(player);
	// Simple Recoil effect
	player->x -= 3;
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("Player fired at position (%d, %d)\n", player->x, player->y);
}

void Jump(Player *player)
{
	savePlayerState(player);
	// Simple jump effect
	player->y -= 10;
	player->color = DARKGREEN; // Change color to indicate Jumping
	ClampPlayerOnScreen(player);
	printf("Player jumped at position (%d, %d)\n", player->x, player->y);
}

void JumpFire(Player *player)
{
	savePlayerState(player);
	// Simple jump and fire effect
	player->y -= 10;
	player->x -= 3;
	player->color = RED; // Change color to indicate firing
	ClampPlayerOnScreen(player);
	printf("\n\nJumping and Firing\n\n");
}

//save the player state to memento varible in player
void savePlayerState(Player *player)
{
	PlayerState *state = createPlayerState(player);
	player->memento = createMemento(state);
}

void undo(Player *player)
{
	player->state = getPlayerState(player->memento);
}
