#include <iostream>
#include <string>
#include "Pokemon.h"

struct Skill {
    std::string name;
    float damage;

    Skill(std::string name, float damage)
        : name(name), damage(damage) {}
};

class Pokemon {
public:
    // Public attributes
    std::string name;
    std::string level;
    float hp;

    // Skills
    Skill skill1;
    Skill skill2;

    // Constructor
    Pokemon(std::string name, std::string level, float hp, Skill skill1, Skill skill2)
        : name(name), level(level), hp(hp), skill1(skill1), skill2(skill2) {}

    // Public methods
    void render(int positionX, int positionY, float scale, int direction) {
        // Render the Pokémon based on its position, scale, and direction.
        std::cout << "Rendering " << name << " at (" << positionX << ", " << positionY << "), "
                  << "scale: " << scale << ", direction: " << direction << std::endl;
    }

    void attackAnimation() {
        // Placeholder for attack animation
        std::cout << name << " performs an attack animation!" << std::endl;
    }

    void takeDamage(float damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
        std::cout << name << " takes " << damage << " damage! Current HP: " << hp << std::endl;
        damageAnimation();
    }

    void damageAnimation() {
        // Placeholder for damage animation
        std::cout << name << " displays a damage animation!" << std::endl;
    }

    void useSkill(int skillIndex) {
        // Uses a skill based on skillIndex (1 for skill1, 2 for skill2)
        if (skillIndex == 1) {
            std::cout << name << " uses " << skill1.name << " causing " << skill1.damage << " damage!" << std::endl;
            renderSkillEffect(skill1);
        } else if (skillIndex == 2) {
            std::cout << name << " uses " << skill2.name << " causing " << skill2.damage << " damage!" << std::endl;
            renderSkillEffect(skill2);
        } else {
            std::cout << "Invalid skill index." << std::endl;
        }
    }

private:
    void renderSkillEffect(const Skill& skill) {
        // Render the effect of the skill
        std::cout << "Rendering effect of skill " << skill.name << std::endl;
    }
};
