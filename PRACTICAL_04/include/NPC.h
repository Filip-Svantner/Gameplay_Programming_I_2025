#ifndef NPC_H
#define NPC_H

#include <./include/GameObject.h> // Include the GameObject header

// NPC is a GameObject
class NPC : public GameObject
{
    int choice = 0; // Stores the random generated value for NPC
    int groundStompShockwaveCooldown = 0; // Stores cooldown of ground stomp shockwave
    int clubSmashCooldown = 0; // Stores cooldown for club smash
    int thickHideCooldown = 0; // Stores cooldown for thick hide
public:
    NPC(std::string name, int health = 100) : GameObject(name, health) {} // Constructor to initialize name and health

    void taunt();                             // Method for NPC to taunt the player
    void walk() override;                     // Specific implementation of walk()
    void attack(GameObject& target) override; // Implementation of pure virtual attack method
    void defend() override;                   // Optionally override defend method
};

#endif // NPC_H
