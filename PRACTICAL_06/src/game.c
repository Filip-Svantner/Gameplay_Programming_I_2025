#include "raylib.h"
#include "stdio.h"
#include "math.h"
#include "../include/game.h"
#include "../include/collision.h"

//graphic variables
int circlePosX = 400; // Default x position of a tree (circle)
int circlePosY = 300; // Default y position of a tree (circle)

int distance = 121*sqrt(2); // side of the pythagorean triangle (2 * distance^2 = radius^2)
int radius = 242; // Radius of a circle the trees are in 



Color playerColor = WHITE;
Color trunks = BROWN;
Color crowns = GREEN;
Color background = GRAY;

//sprite variables
Texture2D spriteRight, spriteLeft, sprite; // Stores textures
Image image; // used for mirroring the sprite texture

Vector2 direction = {0,0}; // direction of player
Vector2 position = {400 - 80, 300 - 80}; // position of player (moved of center, because image is scaled)
int velocity = 5; // value by which the position change

bool isDrawing = true;

CircleStruct playerCircle;

RectangleStruct playerRectangle;

CircleStruct crownsArray[8];
RectangleStruct trunksArray[8];


void InitGame() {
    printf("Game Initialized!\n");
   
    //initialization of the sprites and image
    spriteRight = LoadTexture("resources/player.png");
    image = LoadImageFromTexture(spriteRight);
    ImageFlipHorizontal(&image);
    spriteLeft = LoadTextureFromImage(image);
    sprite = spriteRight;
	
	playerCircle = (CircleStruct){(int)(position.x) + 82, (int)(position.y) + 110, 50};
	playerRectangle = (RectangleStruct){(int)(position.x) + 45, (int)(position.y) + 65, 75, 90};
	crownsArray[0] = (CircleStruct){circlePosX, circlePosY - radius, 50};
	crownsArray[1] = (CircleStruct){circlePosX , circlePosY + radius, 50};
	crownsArray[2] = (CircleStruct){circlePosX - radius, circlePosY, 50};
	crownsArray[3] = (CircleStruct){circlePosX + radius, circlePosY, 50};
	crownsArray[4] = (CircleStruct){circlePosX + distance, circlePosY + distance, 50};
	crownsArray[5] = (CircleStruct){circlePosX + distance, circlePosY - distance, 50};
	crownsArray[6] = (CircleStruct){circlePosX - distance, circlePosY + distance, 50};
	crownsArray[7] = (CircleStruct){circlePosX - distance, circlePosY - distance, 50};
	trunksArray[0] = (RectangleStruct){circlePosX - 20, circlePosY - radius, 40, 60};
	trunksArray[1] = (RectangleStruct){circlePosX - 20, circlePosY + radius, 40, 60};
	trunksArray[2] = (RectangleStruct){circlePosX + radius - 20, circlePosY, 40, 60};
	trunksArray[3] = (RectangleStruct){circlePosX - radius - 20, circlePosY, 40, 60};
	trunksArray[4] = (RectangleStruct){circlePosX + distance - 20, circlePosY - distance, 40, 60};
	trunksArray[5] = (RectangleStruct){circlePosX + distance - 20, circlePosY + distance, 40, 60};
	trunksArray[6] = (RectangleStruct){circlePosX - distance - 20, circlePosY - distance, 40, 60}; 
	trunksArray[7] = (RectangleStruct){circlePosX - distance - 20, circlePosY + distance, 40, 60};
}

void UpdateGame() {
	
	for(int i = 0; i < 8; i++)
	{
		if(circleToCircle(&playerCircle, &crownsArray[i]))
		{
			playerColor = RED;
		}
	}
	
	for(int e = 0; e < 8; e++)
	{
		if(rectangleToRectangle(&playerRectangle, &trunksArray[e]))
		{
			playerColor = BLUE;
		}
	}		
    
    //int of KEY_RIGHT = 1, KEY_LEFT = -1
    direction.x = (int)(IsKeyDown(KEY_RIGHT)) - (int)(IsKeyDown(KEY_LEFT));
    direction.y = (int)(IsKeyDown(KEY_DOWN)) - (int)(IsKeyDown(KEY_UP));
    
    if(direction.x > 0) // if player is moving right, image looks right
    {
    	sprite = spriteRight;
    }
    else if (direction.x < 0) // if player is moving left, image looks left
    {
    	sprite = spriteLeft;
    }

    position.x += direction.x * velocity; //updating the position with velocity
    position.y += direction.y * velocity;

    if(IsKeyDown(KEY_X)) // if x is being pressed the screen changes color
    {
    	playerColor = RED;
	trunks = MAROON;
	background = BLACK;
	crowns = PURPLE;

    }
    else // else its normal
    {
	playerColor = WHITE;
	trunks = BROWN;
	background = GRAY;
	crowns = GREEN;
    }

    if(IsMouseButtonDown(0)) //if left mouse button is being pressed, don't draw anything
    {
	isDrawing = false;
    }
    else
    {
	isDrawing = true;
    }
}

void DrawGame() {

    if (isDrawing) {
	DrawRectangle(0, 0, 800, 600, background);
    
	Pentagram();
	Trunks();
	Crowns();
    
	DrawRectangle(position.x + 45, position.y + 65, 75, 90, GREEN);
	DrawCircle(position.x + 82, position.y + 110, 50, YELLOW);
	DrawTextureEx(sprite, position, 0, 5, playerColor);
    }
    
	   
}

//used for drawing the trunks of the trees
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

//used for drawing the tree crowns
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

//used for drawing the pentagram
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

    //unloads all the textures and image
    UnloadTexture(sprite);
    UnloadTexture(spriteLeft);
    UnloadTexture(spriteRight);
    UnloadImage(image);

    printf("Game Closed!\n");
}