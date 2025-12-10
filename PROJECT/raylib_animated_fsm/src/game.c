#include <stdio.h>
#include <raylib.h>

#include "./game/game.h"

#include "./utils/input_manager.h"
#include "./utils/ai_manager.h"

/**
 * InitGame : Sets everything up before the madness begins.
 *
 * Creates the player, the NPC, and the two mediators that stop them
 * shouting directly at the FSM. Also fires up the input and AI systems.
 * Oh and as Ireland is so green (from all the rain), a nice lush grass background.
 *
 * @data: The GameData structure that holds the whole operation together
 */

void InitGame(GameData *data)
{
	// printf("Game Initialised!\n");
	data->state = MENU;

	//----GAME DATA-----
	// Initialize the player and NPC with their respective names
	// Setup position
	Vector2 playerPosition = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
	Vector2 npcPosition = (Vector2){GetScreenWidth() / 2.0f, 100.0f};

	data->player = InitPlayer("Player Hero", playerPosition, DEFAULT_GAMEOBJECT_RADIUS);
	data->npc = InitNPC("The Villan", npcPosition, DEFAULT_GAMEOBJECT_RADIUS);

	// Create a mediator to facilitate communication between
	// Command and FSM, ultimately updating the playes state
	// Create Mediators
	data->playerMediator = CreateMediator((GameObject *)data->player);
	data->npcMediator = CreateMediator((GameObject *)data->npc);

	//-----IMAGES-----
	// Background Grass... looks better than a plain background
	// https://github.com/raysan5/raylib/blob/master/examples/textures/textures_image_generation.c
	Image grass = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 80, 80, 6.0f);
	ImageFormat(&grass, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkGrass = (Color){20, 66, 63, 255};
	Color lightGrass = (Color){48, 107, 64, 255};

	Image dirt = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 30, 30, 4.0f);
	ImageFormat(&dirt, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkDirt = (Color){58, 39, 43, 255};
	Color lightDirt = (Color){92, 70, 62, 255};

	// https://www.color-hex.com/color-palette/46612
	Image rocks = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 20, 20, 3.0f);
	ImageFormat(&rocks, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	// https://www.color-hex.com/color-palette/46612
	Color darkRocks = (Color){90, 76, 66, 255};
	Color lightRocks = (Color){163, 162, 165, 255};

	// PixelData
	Color *grassPixels = (Color *)grass.data;
	Color *dirtPixels = (Color *)dirt.data;
	Color *rockPixels = (Color *)rocks.data;

	// Acts like a fragment shader coloring each pixel
	int pixelCount = SCREEN_WIDTH * SCREEN_HEIGHT;

	// Precalculate for performance
	const int deltaGrassRed = lightGrass.r - darkGrass.r;
	const int deltaGrassGreen = lightGrass.g - darkGrass.g;
	const int deltaGrassBlue = lightGrass.b - darkGrass.b;

	const int deltaDirtRed = lightDirt.r - darkDirt.r;
	const int deltaDirtGreen = lightDirt.g - darkDirt.g;
	const int deltaDirtBlue = lightDirt.b - darkDirt.b;

	const int deltaRocksRed = lightRocks.r - darkRocks.r;
	const int deltaRocksGreen = lightRocks.g - darkRocks.g;
	const int deltaRocksBlue = lightRocks.b - darkRocks.b;

	for (int i = 0; i < pixelCount; i++)
	{
		// Use green component like a scale (normalised)
		float t = grassPixels[i].g * (1 / 255.0f);
		float noise = grassPixels[i].b * (1 / 255.0f);

		if (dirtPixels[i].r < 55)
		{
			grassPixels[i].r = darkDirt.r + (unsigned char)(t * deltaDirtRed);
			grassPixels[i].g = darkDirt.g + (unsigned char)(t * deltaDirtGreen);
			grassPixels[i].b = darkDirt.b + (unsigned char)(t * deltaDirtBlue);
		}
		else if (rockPixels[i].r < 70)
		{
			grassPixels[i].r = darkRocks.r + (unsigned char)(t * deltaRocksRed);
			grassPixels[i].g = darkRocks.g + (unsigned char)(t * deltaRocksGreen);
			grassPixels[i].b = darkRocks.b + (unsigned char)(t * deltaRocksBlue);
		}
		else
		{
			grassPixels[i].r = darkGrass.r + (unsigned char)(t * deltaGrassRed);
			grassPixels[i].g = darkGrass.g + (unsigned char)(t * deltaGrassGreen);
			grassPixels[i].b = darkGrass.b + (unsigned char)(t * deltaGrassBlue);
		}
		grassPixels[i].a = 148 + (unsigned char)(noise * 30.0f);
	}

	// Blended grass set as background
	data->background = LoadTextureFromImage(grass);
	UnloadImage(grass); // Free up as Texture was produced
	UnloadImage(dirt);	// Free up as Texture was produced
	UnloadImage(rocks); // Free up as Texture was produced

	GameButtons *initButtons = (GameButtons *)malloc(sizeof(GameButtons));
	data->buttons = initButtons;

	Button *initMenuButton = (Button *)malloc(sizeof(Button));
	data->buttons->menuButton = initMenuButton;
	Button *initPlayButton = (Button *)malloc(sizeof(Button));
	data->buttons->playButton = initPlayButton;
	Button *initControlsButton = (Button *)malloc(sizeof(Button));
	data->buttons->controlsButton = initControlsButton;
	Button *initExitButton = (Button *)malloc(sizeof(Button));
	data->buttons->exitButton = initExitButton;

	data->buttons->menuButton->texture = LoadTexture("assets/menu_button.png");
    data->buttons->playButton->texture = LoadTexture("assets/play_button.png");
    data->buttons->controlsButton->texture = LoadTexture("assets/controls_button.png");
    data->buttons->exitButton->texture = LoadTexture("assets/exit_button.png");

	data->buttons->playButton->isSelected = true;
	data->buttons->playButton->color = GRAY;

	data->buttons->menuButton->color = WHITE;
	data->buttons->controlsButton->color = WHITE;
	data->buttons->exitButton->color = WHITE;

	data->endGame = false;

	data->buttonTimer = 0.0f;
	
	// Initialise Input Managers
	InitInputManager();
	InitAIManager();
}

/**
 * UpdateGame : Runs one tick of game logic.
 *
 * Handles player input, NPC behaviour, state updates, and collisions.
 * The NPC gets a new "idea" every second, which is generous given its low IQ.
 *
 * @data:      All the game's current state.
 * @deltaTime: Time since the last update.
 */

void UpdateGame(GameData *data, float deltaTime)
{
	if(data->state == GAMEOVER)
	{
		if(MediatorUpdateGameOver())
		{
			InitGame(data);
		}
	}
	if(data->state == MENU)
	{
		int input = 1;
		data->buttonTimer+=deltaTime;

		if(data->buttonTimer > 0.1f)
		{
			if(data->buttons->playButton->isSelected)
			{
				input = MediatorUpdateMenu(1);
				if(input == 0)
				{
					data->state = GAME;
				}
				else
				{
					selectButton(data->buttons, input);
				}
			}
			else if(data->buttons->controlsButton->isSelected)
			{
				input = MediatorUpdateMenu(2);
				if(input == 0)
				{
					data->state = CONTROLS;
				}
				else
				{
					selectButton(data->buttons, input);
				}
			}
			else
			{
				input = MediatorUpdateMenu(3);
				if(input == 0)
				{
					data->endGame = true;
				}
				else
				{
					selectButton(data->buttons, input);
				}
			}
			data->buttonTimer = 0.0f;
		}
	}
	if(data->state == GAME)
	{
		if(data->player->base.lives == 0 || data->npc->base.lives == 0)
		{
			data->state = GAMEOVER;
		}
		// Poll input from the player and execute the corresponding command
		MediatorUpdatePlayer(data->playerMediator, deltaTime); // Execute the command via the mediator

		// Update the player's state based on its current configuration
		UpdateState(&data->player->base, deltaTime);

		// Update NPC
		MediatorUpdateNPC(data->npcMediator, deltaTime);

		// If the NPC is attacking, update its target to the player's position
		// This makes the NPC chase the player
		if (data->npc->base.currentState == STATE_ATTACKING)
		{
			data->npc->target = data->player->base.position;
			data->npc->aggression += NPC_AGGRESSION_BUILD * deltaTime; // Increase aggression over time while attacking
			if (data->npc->aggression > NPC_MAX_AGGRESSION)
				data->npc->aggression = NPC_MAX_AGGRESSION;
		}
		else
		{
			// Reduce agression when not attacking
			data->npc->aggression -= NPC_AGGRESSION_DECAY * deltaTime;
			if (data->npc->aggression < NPC_MIN_AGGRESSION)
				data->npc->aggression = NPC_MIN_AGGRESSION; // Minimum agression
		}

		// Update the NPC's state after handling the event
		UpdateState(&data->npc->base, deltaTime);

		// Check for Collisions
		bool isColliding = CheckCollision(&data->player->base, &data->npc->base);

		// ENTER Collision
		if (isColliding && !data->player->base.isColliding)
		{
			// Notify FSMs
			HandleEvent(&data->player->base, EVENT_COLLISION_START, deltaTime);
			HandleEvent(&data->npc->base, EVENT_COLLISION_START, deltaTime);

			// Respond to Collision
			CollisionEntry(&data->player->base, &data->npc->base);
			HandleCollision(&data->player->base, &data->npc->base);
		}
		else if (!isColliding && data->player->base.isColliding)
		{
			// EXIT Collision
			HandleEvent(&data->player->base, EVENT_COLLISION_END, deltaTime);
			HandleEvent(&data->npc->base, EVENT_COLLISION_END, deltaTime);

			CollisionExit(&data->player->base, &data->npc->base);
		}
		else if (isColliding && data->player->base.isColliding)
		{
			// ONGOING Collision
			HandleCollision(&data->player->base, &data->npc->base);
		}

		// Update isColliding for GameObjects
		data->player->base.isColliding = isColliding;
		data->npc->base.isColliding = isColliding;

	}
}

// Draw GameObject HealthBar
static void DrawGameObjectHealthBar(const GameObject *object)
{
	
	// Healthbar Dimensions
	const int healthBarWidth = 100;
	const int healthBarHeight = 10;

	// Center above GameObject
	const int healthBarX = object->position.x - (healthBarWidth / 2);
	const int healthBarY = object->position.y - 40;

	// Make sure health is between 0 and 100
	int health = object->health;
	if (health < 0)
		health = 0;
	if (health > 100)
		health = 100;

	// Bar width
	float healthPercentage = health / 100.0f;
	int currentHealth = (int)(healthBarWidth * healthPercentage);
	int lostHealth = healthBarWidth - currentHealth;
	lostHealth = Clamp(lostHealth, 0, healthBarWidth);

	// Colours
	Color background = ColorAlpha(GRAY, 0.5f);
	Color currentHealthColor = ColorAlpha(GREEN, 0.5f);
	Color lostHealthColor = ColorAlpha(RED, 0.5f);

	// Background (gray)
	DrawRectangle(healthBarX, healthBarY, healthBarWidth, healthBarHeight, background);

	// Current health (green)
	DrawRectangle(healthBarX, healthBarY, currentHealth, healthBarHeight, currentHealthColor);

	// Lost health (red)
	DrawRectangle(healthBarX + currentHealth, healthBarY, lostHealth, healthBarHeight, lostHealthColor);
}

static void DrawStaminaBar(const Player *player)
{
	
	// Stamina Dimensions
	const int staminaBarWidth = 100;
	const int staminaBarHeight = 35;

	// Center above GameObject
	const int staminaBarX = 600;
	const int staminaBarY = 550;

	// Make sure stamina is between 0 and 100
	int stamina = player->stamina;
	if (stamina < 0)
		stamina = 0;
	if (stamina > 100)
		stamina = 100;

	// Bar width
	float staminaPercentage = stamina / 100.0f;
	int currentStamina = (int)(staminaBarWidth * staminaPercentage);
	

	// Colours
	Color background = ColorAlpha(GRAY, 0.5f);
	Color currentStaminaColor = ColorAlpha(BLUE, 0.5f);

	// Background (gray)
	DrawRectangle(staminaBarX, staminaBarY, staminaBarWidth, staminaBarHeight, background);

	// Current health (green)
	DrawRectangle(staminaBarX, staminaBarY, currentStamina, staminaBarHeight, currentStaminaColor);
}

// Draw the GameObject in this example a simple Circle which is a collider
static void DrawGameObjectColliderCircle(const GameObject *object)
{
	// Set alpha for collisision circle
	Color background = ColorAlpha(object->color, 0.5f);

	// Circle Thickness
	int thickness = 5;

	// GameObject Circle
	DrawRing(
		object->position,					// Vector2 (x, y)
		object->collider.r - thickness / 2, // inner radius
		object->collider.r + thickness / 2, // outer radius
		0.0f, 360.0f,						// start angle, end angle
		64,									// segments
		background							// Color
	);
}

// Draw position information at the bottom of the GameObject
static void DrawGameObjectPositionInfo(const GameObject *object)
{
	const char *information = TextFormat("(%.f, %.f)",
										 object->position.x,
										 object->position.y);
	DrawText(
		information,
		object->position.x - (MeasureText(information, 20) / 2), // Measure the text with with MeasureText
		object->position.y + 30,								 // Place it below the GameObject
		20, DARKGRAY);
}

void DrawMenuScreen(const GameData *data)
{
	DrawTexture(data->buttons->menuButton->texture, 100,100,data->buttons->menuButton->color);
	DrawTexture(data->buttons->playButton->texture, 200,300,data->buttons->playButton->color);
	DrawTexture(data->buttons->controlsButton->texture, 200,400,data->buttons->controlsButton->color);
	DrawTexture(data->buttons->exitButton->texture, 200,500,data->buttons->exitButton->color);
}

void DrawGameOver(const GameData *data)
{
	if(data->player->base.lives == 0)
	{
		DrawText("You Lost", SCREEN_WIDTH / 2 - MeasureText("You Lost", 100) / 2, 250, DEFAULT_FONT_SIZE, BLACK);
	}
	if(data->npc->base.lives == 0)
	{
		DrawText("You Won", SCREEN_WIDTH / 2 - MeasureText("You Won", 100) / 2, 250, DEFAULT_FONT_SIZE, BLACK);
	}
	DrawText("You Won", SCREEN_WIDTH / 2 - MeasureText("You Won", 100) / 2, 400, DEFAULT_FONT_SIZE, BLACK);
}

/**
 * DrawGame : Draws all the craic on screen.
 *
 * Renders the player, the NPC, their positions, health bars,
 * and whatever animations they've decided to show off.
 *
 * @data: The game state to render.
 */

void DrawGame(const GameData *data)
{
	// Draw Background
	DrawTexture(data->background, 0, 0, WHITE);

	if(data->state == MENU)
	{
		DrawMenuScreen(data);
	}

	if(data->state == GAME)
	{
		// Draw some basic UI text (game title and description)
		DrawFPS(10, 20);
		char livesMessage[20];
		sprintf(livesMessage, "Lives: %d", data->player->base.lives);
		DrawText( livesMessage, 10, 550, 50, RED);
		DrawStaminaBar(data->player);

		//---------------------------------------------------------
		// Drawing NPC and Position Data
		// NPC Circle
		//---------------------------------------------------------
		DrawGameObjectColliderCircle(&data->npc->base);

		// Render the npc's animation at their current position
		DrawAnimation(&data->npc->base.animation, data->npc->base.position, RAYWHITE);

		// Player Position Information
		DrawGameObjectPositionInfo(&data->npc->base);

		// Drawing Health Bar for the npc
		DrawGameObjectHealthBar(&data->npc->base);

		//---------------------------------------------------------
		// Drawing Player and Position Data
		// Player Circle
		//---------------------------------------------------------
		DrawGameObjectColliderCircle(&data->player->base);

		// Render the player's animation at their current position
		DrawAnimation(&data->player->base.animation, data->player->base.position, data->player->superPowerColor);

		// Player Position Information
		DrawGameObjectPositionInfo(&data->player->base);

		// Drawing Health Bar for the player
		DrawGameObjectHealthBar(&data->player->base);
	}
	if(data->state == GAMEOVER)
	{
		DrawGameOver(data);
	}
}

/**
 * CloseGame - Shuts everything down gracefully.
 *
 * Runs the cleanup routine so you're not leaving memory lying around
 * like empty pint glasses after closing time (in Dinn Ri again).
 *
 * @data: The game data to be disposed of.
 */

void CloseGame(GameData *data)
{
	// printf("Game Closed!\n");

	// If the game data is not null, delete all objects associated with the game
	if (data != NULL)
	{
		DeleteGameData(data);
	}
}

void DeleteButtons(GameButtons *buttons)
{
	if(buttons)
	{
		free(buttons);
		buttons = NULL;
	}
}

/**
 * DeleteGameData - Frees every object in the game's data.
 *
 * Deletes player, NPC, mediators, and finally frees the GameData
 * itself. No memory leaks here, thank you very much.
 *
 * @data: The structure to purge (I've watched a few)
 * "The unwritten Purge rule: don't save lives" but do free memory
 */

void DeleteGameData(GameData *data)
{
	if (data != NULL)
	{
		// Delete the player and NPC objects if they are not null
		if (data->player != NULL)
		{
			DeletePlayer(&data->player->base);
		}

		if (data->npc != NULL)
		{
			DeleteNPC(&data->npc->base);
		}

		if (data->playerMediator != NULL)
		{
			DeleteMediator(data->playerMediator);
		}

		if (data->npcMediator != NULL)
		{
			DeleteMediator(data->npcMediator);
		}

		if(data->buttons != NULL)
		{
			DeleteButtons(data->buttons);
		}

		// Free the background
		UnloadTexture(data->background);
		UnloadTexture(data->buttons->controlsButton->texture);
		UnloadTexture(data->buttons->playButton->texture);
		UnloadTexture(data->buttons->menuButton->texture);
		UnloadTexture(data->buttons->exitButton->texture);
	}

	// Free GameData
	free(data); // Free game data memory
}

void selectButton(GameButtons *buttons, int whatActive)
{

	if(whatActive == 1)
	{
		buttons->playButton->isSelected = true;
		buttons->controlsButton->isSelected = false;
		buttons->exitButton->isSelected = false;

		buttons->playButton->color = GRAY;
		buttons->controlsButton->color = WHITE;
		buttons->exitButton->color = WHITE;
	}
	else if(whatActive == 2)
	{
		buttons->playButton->isSelected = false;
		buttons->controlsButton->isSelected = true;
		buttons->exitButton->isSelected = false;

		buttons->playButton->color = WHITE;
		buttons->controlsButton->color = GRAY;
		buttons->exitButton->color = WHITE;
	}
	else
	{
		buttons->playButton->isSelected = false;
		buttons->controlsButton->isSelected = false;
		buttons->exitButton->isSelected = true;

		buttons->playButton->color = WHITE;
		buttons->controlsButton->color = WHITE;
		buttons->exitButton->color = GRAY;
	}
	
}
