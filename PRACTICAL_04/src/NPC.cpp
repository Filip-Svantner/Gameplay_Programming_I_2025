#include <./include/NPC.h> // Include the NPC header
#include <iostream>        // For std::cout
#include <string>          // For std::string

// Method for NPC to taunt the player
void NPC::taunt()
{
    std::cout << name << " taunts you: 'Is that all you've got?'" << std::endl;
}

// Specific implementation of walk()
void NPC::walk()
{
    std::cout << name << " walks forward." << std::endl;
}

// Implementation of pure virtual attack method
void NPC::attack(GameObject &target)
{
    srand(time(NULL));

    bool attacking;

    attacking = true;

    while (attacking)
    {
        if (clubSmashCooldown == 0 || groundStompShockwaveCooldown == 0)
        {
            choice = rand() % 2;

            if (choice == 0)
            {
                if (clubSmashCooldown == 0)
                {
                    std::cout << name << " attacks " << target.getName() << " with club smash!" << std::endl;

                    if (!target.isDefending())
                    {
                        target.takeDamage(20);
                    }
                    else
                    {
                        std::cout << target.getName() << " defended the attack" << "\n";
                        target.setDefending(false);
                    }

                    clubSmashCooldown = 3;
                    attacking = false;
                }
            }
            else
            {
                if (groundStompShockwaveCooldown == 0)
                {

                    std::cout << name << " attacks " << target.getName() << " with ground stomp shockwave!" << std::endl;
                    if (!target.isDefending())
                    {
                        target.takeDamage(10);
                    }
                    else
                    {
                        std::cout << target.getName() << " defended the attack" << "\n";
                        target.setDefending(false);
                    }
                    groundStompShockwaveCooldown = 2;
                    attacking = false;
                }
            }
        }
        else
        {
            std::cout << name << " doesn't attack" << "\n";
            attacking = false;
        }

    }

}

// Optionally override defend method
void NPC::defend()
{
    std::cout << name << " takes a defensive stance." << std::endl;
}
