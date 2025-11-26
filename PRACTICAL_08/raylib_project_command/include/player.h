#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "constants.h"
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
    int health;
    Color color;
}PlayerState;

typedef struct 
{
    PlayerState *state; // Store player state (position, health, etc.

}Memento;

// Player Structure Data
typedef struct
{
    int x;
    int y;
    int r;
    int health;
    float breathTimer;
    Color color;
    PlayerState *state;
    Memento *memento;
} Player;

// PlayerState Behaviours
PlayerState *createPlayerState(Player *t_player);
PlayerState *getPlayerState(Memento *t_memento);

// Memento Behaviours
Memento *createMemento(PlayerState *t_pState);

// Player Behaviours
void Idle(Player *player, float deltaTime);
void MoveUp(Player *player);
void MoveDown(Player *player);
void MoveLeft(Player *player);
void MoveRight(Player *player);

void Jump(Player *player);
void Fire(Player *player);

void JumpFire(Player *player);
void MoveUpFire(Player *player);

void ClampPlayerOnScreen(Player *player); // Player stays within screen bounds

void savePlayerState(Player *player);

void undo(Player *player);

#endif
