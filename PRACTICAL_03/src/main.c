#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

int choice;

//screens
typedef enum
{
  EXIT,
  MENU,
  WAR_HEADS,
  COORDINATES,
  CODE,
  COLLISION,
  RESULT
}Screens;
  
  
// Define Position xy struct
typedef struct Position
{
  int x;
  int y;
} Coordinates;

// Define WarHead enum type
typedef enum
{
  EXPLOSIVE,
  NUCLEAR
} WarHead;

// Define Enemy struct type with Coordinates
typedef struct Enemy
{
  Coordinates coordinates;
} Target;

// Define Missile struct type with WarHead, Coordinates, Target, and armed status
typedef struct Missile
{
  WarHead payload;
  Coordinates coordinates;
  Target target;

  bool armed;

  // ADVANCED: Function pointers (direct function calls can be used instead)
  // Function pointer to update missile position

  void (*update)(struct Missile *missile);

  // Function pointer to arm or disarm missile
  void (*arm)(struct Missile *missile);

} Missile;

// Function to arm or disarm a missile
void armMissile(struct Missile *missile)
{
  if (missile->armed)
    missile->armed = false;
  else
    missile->armed = true;
}

// Function to update missile position
void updateMissile(struct Missile *missile)
{
  missile->coordinates.x += 1;
  missile->coordinates.y += 1;
}

// Function to print coordinates
void printCoordinates(Coordinates c)
{
  printf("X: %d, Y: %d\n", c.x, c.y);
}

//Select war head
Screens selectWarHead(Missile *t_missile)
{
  printf("Select missile: \n");
  printf("1 - Explosive \n");
  printf("2 - Nuclear \n");
  std::cin >> choice;
  if (choice == 1){
    t_missile->payload = EXPLOSIVE;
    return COORDINATES;
  }
  else if (choice == 2){
    t_missile->payload = NUCLEAR;
    return COORDINATES;
  }
  else{
    printf("Invalid choice.\n");
    return WAR_HEADS;
  }

}

Screens selectCoordinates(Missile *t_missile) //used to select coordinates
{
  std::cout << "Choose x coordinate: " ;
  std::cin >> choice; //input of x coordinate
  t_missile->coordinates.x = choice;
  printf("Choose y coordinate: ");
  std::cin >> choice; //input of y coordinate
  t_missile->coordinates.y = choice;
  return CODE;
}

Screens enterCode(Missile *t_missile) // code check
{
  int code = 1234; //code number
  int t_choice;
  int codeCounter = 0; //how many times was code inserted

  while (codeCounter < 4){
  	printf("Enter arming code: ");
 	std::cin >> t_choice;
  		if(t_choice == 1234){
   	// Set Missile Armed Status
 			t_missile->arm(t_missile);
			codeCounter = 0;
  		}
 		 else{
			codeCounter++;
  		}
  }
  if (t_missile->armed)
  {
    return COLLISION;
  }
  else 
  {
    printf("You failed to launch. \n");
    return EXIT;
  }
}

Screens checkCollision(Missile *t_missile, Target *t_target) // checking collision
{
	bool x = false; //if x was hit
	bool y = false; //if y was hit
  if (t_missile->coordinates.x == t_target->coordinates.x)
  {
	  printf("Hit on the x axis. \n");
	  x = true;
  }
  if (t_missile->coordinates.y == t_target->coordinates.y)
  {
	  printf("Hit on the y axis. \n");
	  y = true;
  }
  if (x && y) //if both true game ends
  {
	printf("You destroyed the target. \n");
	return MENU;
  }
	return WAR_HEADS;
}


  

// Main entry point for the game
int main()
{
  Screens screen = MENU;

  // Create a new Missile
  Missile *missile = (Missile *)malloc(sizeof(Missile));

  // Create a new Target
  Target *target = (Target *)malloc(sizeof(Target));

  // Set Enemy Position / Target coordinates
  target->coordinates.x = 10;
  target->coordinates.y = 50;


  while(screen == MENU) //menu screen
  {
	printf("1 - Start game\n");
  	printf("2 - Exit \n");
        std::cin >> choice;
        if (choice == 1){
		screen = WAR_HEADS;
        }
	else{
		screen = EXIT;
	}		
  }
  

  while(screen == WAR_HEADS) //select warheads screen
  {
   screen = selectWarHead(missile);
  }
  

  while(screen == COORDINATES)
  {
   screen = selectCoordinates(missile);
  }

  while(screen == CODE)
  {
   screen = enterCode(missile);
  }
  
  while(screen == COLLISION)
  {
   screen = checkCollision(missile, target);
  }
  
  // Print Target Coordinates
  //printf("Print Target Coordinates\n");
  //printCoordinates(target->coordinates);

  // Set Missile Target by dereferencing Target pointer
  //missile->target = *target;

  // Set Initial Position
  //missile->coordinates.x = 0;
  //missile->coordinates.y = 0;

  // Print Position
  //printf("Print Missile Position\n");
  //printCoordinates(missile->coordinates);

  // Update Position
 // missile->update(missile);

  // Print Missile Position
  //printf("Print Missile Position after an Update\n");
  //printCoordinates(missile->coordinates);

  // Print Missile target
  //printf("Print Missile Target Position\n");
  //printCoordinates(missile->target.coordinates);

  // Free Memory
  free(target);
  free(missile);

  // Pause
  printf("Press Enter to end game.\n");
  getchar();

  return 0;
}
