#include <./include/Player.h>        // Include the Player header
#include <iostream>       // For std::cout
#include <string>         // For std::string

// Method for Player to charge at an enemy
void Player::charge() {
    std::cout << name << " charges at the enemy!" << std::endl;
}

// Specific implementation of walk()
void Player::walk() {
    std::cout << name << " walks forward." << std::endl;
}

// Implementation of pure virtual attack method
void Player::attack(GameObject& target) {
    bool attacking;

    attacking = true;

    while (attacking)
    {
        std::cout << "Choose attack: " << "\n";
        std::cout << "1 - Sword slash (" << cooldownDisplay(swordSlashCooldown) << ") " << "\n";
        std::cout << "2 - Shield bash (" << cooldownDisplay(shieldBashCooldown) << ") " << "\n";
        std::cout << "0 - No attack " << "\n";
        std::cin >> choice;

        if (choice == 0)
        {
            std::cout << name << " doesn't attack" << "\n";
            attacking = false;
        }
        else if (choice == 1)
        {
            if (swordSlashCooldown > 0)
            {
                std::cout << "Not on cooldown, will be available in " << swordSlashCooldown << " turns" << "\n";
            }
            else
            {
                std::cout << name << " attacks " << target.getName() << " with sword slash!" << std::endl;
                
                if (!target.isDefending())
                {
                    target.takeDamage(20);
                }
                else
                {
                    std::cout << target.getName() << " defended the attack" << "\n";
                    target.setDefending(false);
                }

                swordSlashCooldown = 3;
                attacking = false;
            }
        }
        else if (choice == 2)
        {
            if (shieldBashCooldown > 0)
            {
                std::cout << "Not on cooldown, will be available in " << shieldBashCooldown << " turns" << "\n";
            }
            else
            {
                std::cout << name << " attacks " << target.getName() << " with shield bash!" << std::endl;
                if (!target.isDefending())
                {
                    target.takeDamage(10);
                }
                else
                {
                    std::cout << target.getName() << " defended the attack" << "\n";
                    target.setDefending(false);
                }
                shieldBashCooldown = 2;
                attacking = false;
            }
        }
        else
        {
            std::cout << "Invalid input." << "\n";
        }

    }

}

// Optionally override defend method
void Player::defend() {
    std::cout << name << " takes a defensive stance." << std::endl;
}
