#include "raylib.h"
#include "stdio.h"
#include "math.h"
#include "../include/game.h"

int circlePosX = 400;
int circlePosY = 300;
int distance = 121*sqrt(2);
int radius = 242;
Texture2D spriteRight, spriteLeft, sprite;
Image image;
Vector2 direction = {0,0};
Vector2 position = {400 - 80, 300 - 80};
int velocity = 5;
int rotation = 0;

Color playerColor = WHITE;
Color trunks = BROWN;
Color crowns = GREEN;
Color background = GRAY;


void InitGame() {
    printf("Game Initialized!\n");
    spriteRight = LoadTexture("resources/player.png");
    image = LoadImageFromTexture(spriteRight);
    ImageFlipHorizontal(&image);
    spriteLeft = LoadTextureFromImage(image);
    sprite = spriteRight;
}

void UpdateGame() {
    
    direction.x = (int)(IsKeyDown(KEY_RIGHT)) - (int)(IsKeyDown(KEY_LEFT));
    direction.y = (int)(IsKeyDown(KEY_DOWN)) - (int)(IsKeyDown(KEY_UP));
    if(direction.x > 0)
    {
    	sprite = spriteRight;
    }
    else if (direction.x < 0)
    {
    	sprite = spriteLeft;
    }
    position.x += direction.x * velocity;
    position.y += direction.y * velocity;

    if(IsKeyDown(KEY_X))
    {
    	playerColor = RED;
	trunks = MAROON;
	background = BLACK;
	crowns = PURPLE;

    }
    else 
    {
	playerColor = WHITE;
	trunks = BROWN;
	background = GRAY;
	crowns = GREEN;
    }
}

void DrawGame() {
    DrawRectangle(0, 0, 800, 600, background);
    
    Pentagram();
    Trunks();
    Crowns();
    
    DrawTextureEx(sprite, position, rotation, 5, playerColor);
    
	   
}

void Trunks() {

    DrawTriangle((Vector2){circlePosX - 20, circlePosY - radius + 60}, (Vector2){circlePosX + 20, circlePosY - radius + 60}, (Vector2){circlePosX, circlePosY - radius}, trunks);
    DrawTriangle((Vector2){circlePosX - 20, circlePosY + radius + 60}, (Vector2){circlePosX + 20, circlePosY + radius + 60}, (Vector2){circlePosX, circlePosY + radius}, trunks);

    DrawTriangle((Vector2){circlePosX + radius - 20, circlePosY + 60}, (Vector2){circlePosX + radius + 20, circlePosY + 60}, (Vector2){circlePosX + radius, circlePosY}, trunks);
    DrawTriangle((Vector2){circlePosX - radius - 20, circlePosY + 60}, (Vector2){circlePosX - radius + 20, circlePosY + 60}, (Vector2){circlePosX - radius, circlePosY}, trunks);

    DrawTriangle((Vector2){circlePosX + distance - 20, circlePosY - distance + 60}, (Vector2){circlePosX + distance + 20, circlePosY - distance + 60}, (Vector2){circlePosX + distance, circlePosY - distance}, trunks);
    DrawTriangle((Vector2){circlePosX + distance - 20, circlePosY + distance + 60}, (Vector2){circlePosX + distance + 20, circlePosY + distance + 60}, (Vector2){circlePosX + distance, circlePosY + distance}, trunks);

    DrawTriangle((Vector2){circlePosX - distance - 20, circlePosY - distance + 60}, (Vector2){circlePosX - distance + 20, circlePosY - distance + 60}, (Vector2){circlePosX - distance, circlePosY - distance}, trunks);
    DrawTriangle((Vector2){circlePosX - distance - 20, circlePosY + distance + 60}, (Vector2){circlePosX - distance + 20, circlePosY + distance + 60}, (Vector2){circlePosX - distance, circlePosY + distance}, trunks);
}

void Crowns() {

    DrawCircle(circlePosX, circlePosY - radius, 50, crowns);
    DrawCircle(circlePosX, circlePosY + radius, 50, crowns);

    DrawCircle(circlePosX + radius, circlePosY, 50, crowns);
    DrawCircle(circlePosX - radius, circlePosY, 50, crowns);

    DrawCircle(circlePosX + distance, circlePosY - distance, 50, crowns);
    DrawCircle(circlePosX + distance, circlePosY + distance, 50, crowns);

    DrawCircle(circlePosX - distance, circlePosY - distance, 50, crowns);
    DrawCircle(circlePosX - distance, circlePosY + distance, 50, crowns);

}

void Pentagram() {

    DrawLineEx((Vector2){400, 100},(Vector2) {200, 400}, 5, RED);
    DrawLineEx((Vector2){400, 100},(Vector2) {200, 400}, 2, ORANGE);

    DrawLineEx((Vector2){200, 400},(Vector2) {650, 200}, 5, RED);
    DrawLineEx((Vector2){200, 400},(Vector2) {650, 200}, 2, ORANGE);

    DrawLineEx((Vector2){650, 200},(Vector2) {150, 200}, 5, RED);
    DrawLineEx((Vector2){650, 200},(Vector2) {150, 200}, 2, ORANGE);

    DrawLineEx((Vector2){150, 200},(Vector2) {600, 400}, 5, RED);
    DrawLineEx((Vector2){150, 200},(Vector2) {600, 400}, 2, ORANGE);

    DrawLineEx((Vector2){600, 400},(Vector2) {400, 100}, 5, RED);
    DrawLineEx((Vector2){600, 400},(Vector2) {400, 100}, 2, ORANGE);

}

void CloseGame() {
    UnloadTexture(sprite);
    UnloadTexture(spriteLeft);
    UnloadTexture(spriteRight);
    UnloadImage(image);
    printf("Game Closed!\n");
}