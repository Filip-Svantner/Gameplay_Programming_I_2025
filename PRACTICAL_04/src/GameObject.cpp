#include <./include/GameObject.h>

// Implementation of GameObject Methods

// Getter for name, marked as const
std::string GameObject::getName() const
{
    return name;
}

// Getter for health, marked as const
int GameObject::getHealth() const
{
    return health;
}

// Default defend implementation
void GameObject::defend()
{
    std::cout << name << " GameObject : Defending..." << std::endl;
}

// Default walk implementation
void GameObject::walk()
{
    std::cout << name << " GameObject : Walking..." << std::endl;
}

// Default takeDamage implementation
void GameObject::takeDamage(int damage)
{
    health -= damage;
    std::cout << name << " GameObject : Takes Damage : " << damage << " Health : " << health << std::endl;
}

std::string GameObject::cooldownDisplay(int t_cooldown) const
{
    if (t_cooldown > 0)
    {
        return std::to_string(t_cooldown) + " turns";
    }
    else
    {
        return "ready";
    }
}

bool GameObject::isDefending() const
{
    return defending;
}

void GameObject::setDefending(bool t_isDefending)
{
    defending = t_isDefending;
}

