#include <iostream>

#include <./include/Player.h>
#include <./include/NPC.h>

using namespace std;

class Game
{
private:
    Player player;
    NPC npc;
	int mainChoice = 0;
	
	
	
public:
	
	bool runGame = true; // stores if the program is running or not
	GameObject *winner = nullptr; 
	
	enum class Screens // enum class for screens
	{
		EXIT,
		GAMEPLAY,
		HOW_TO_PLAY,
		MENU
	};
	
	Screens activeScreen = Screens::MENU; // active screen





    Game() : player("Orc (Player)"), npc("Troll (Boss)") {}
	
	void menuLoop() // menu screen loop
	{
		cout << "Orcs VS Trolls" << "\n";
		cout << "1 - Start game" << "\n";
		cout << "2 - How to play" << "\n";
		cout << "0 - Exit" << "\n";
		cin >> mainChoice;
		
		if(mainChoice > -1 && mainChoice < 3)
		{
			activeScreen = static_cast<Screens>(mainChoice);
		}
		else
		{
			cout << "Invalid input. " << "\n";
		}
	}
	
	void HTPLoop() // how to play screen loop
	{
		cout << "How to play: " << "\n";
		cout << "Every turn you can choose out of 2 attacks. " << "\n";
		cout << "After that you decide either you defend or not." << "\n";
		cout << "Then is the opponent turn. " << "\n";
		cout << "Repeat until victory." << "\n";
		cout << "0 - back to menu." << "\n";
		cin >> mainChoice;
		
		if(mainChoice==0)
		{
			activeScreen = Screens::MENU;
		}
		else
		{
			cout << "Invalid input. " << "\n";
		}
	}
	
	
    void gameloop()
    {
        cout << "Let make a virtual ;-) Turn Based Console Game" << endl;

        // Uncomment and try to compile. Why are errors produced?
        // GameObject go; // Error: Cannot instantiate an abstract class (GameObject has pure virtual methods)
        // go.attack(); // Error: attack is a pure virtual method

        // Uncomment and try to compile. What happens when we try to access a pure virtual method directly?
        // NPC npc;
        // npc.attack(nullptr); // Error: attack is a pure virtual method - Cannot call this directly from the base class

        // Uncomment and try to compile. What happens if we try to access a non-virtual method?
        // NPC npc;
        // npc.getHealth(); // This is fine, but if getHealth() is not overridden, it uses the base class method

        cout << "Let go create a Player" << endl;
        player.walk(); // Method call walk() - Bound at compile time to Player's walk()

        cout << "Let go create an NPC" << endl;
        npc.walk(); // Method call walk() - Bound at compile time to NPC's walk()

        // Uncomment to see the issue with calling the pure virtual method
        // player.attack(nullptr); // Error: Cannot call attack on Player; it must be implemented
		
        // Main GameLoop
        while (player.getHealth() > 0 && npc.getHealth() > 0)
        {
            // Assign Player memory address to GameObject pointer
            GameObject *ptr_plyr = &player;
            ptr_plyr->walk();      // Bound at runtime -> action based on pointer (Player's walk())
            ptr_plyr->attack(npc); // Player attacks NPC through GameObject pointer - Bound at runtime to Player's attack()
            ptr_plyr->defend();    // Player defends through GameObject pointer - Bound at runtime to Player's defend()

            // Assign NPC memory address to GameObject pointer
            GameObject *ptr_npc = &npc;
            ptr_npc->walk();         // Bound at runtime -> action based on pointer (NPC's walk())
            ptr_npc->attack(player); // NPC attacks Player through GameObject pointer - Bound at runtime to NPC's attack()
            ptr_npc->defend();       // NPC defends through GameObject pointer - Bound at runtime to NPC's defend()

            // Check for winner
            if (player.getHealth() <= 0)
            {
                winner = &npc;
				runGame = false;
				activeScreen = Screens::EXIT;
				std::cout << winner->getName() << " has won the battle!" << std::endl;
                break; // End loop if winner is determined
            }
            else if (npc.getHealth() <= 0)
            {
                winner = &player;
				runGame = false;
				activeScreen = Screens::EXIT;
				std::cout << winner->getName() << " has won the battle!" << std::endl;
                break; // End loop if winner is determined
            }
        }
    }
};

int main()
{
    Game game;
	while(game.runGame) // so the screens and functions work smoother
	{
		while (game.activeScreen == Game::Screens::MENU)
		{
			game.menuLoop();
		}
	
		while (game.activeScreen == Game::Screens::HOW_TO_PLAY)
		{
			game.HTPLoop();
		}
		while (game.activeScreen == Game::Screens::GAMEPLAY)
		{
			game.gameloop();
		}
	}
    cin.get();
	return 0;
}
