#include <iostream>
#include "Pokemon.h"

// Constructor for Skill
Skill::Skill(std::string name, float damage)
    : name(name), damage(damage) {}

// Constructor for Pokemon
Pokemon::Pokemon(std::string name, std::string level, float hp, Skill skill1, Skill skill2)
    : name(name), level(level), hp(hp), skill1(skill1), skill2(skill2) {}

// Render function
void Pokemon::render(int positionX, int positionY, float scale, int direction) {
    std::cout << "Rendering " << name << " at (" << positionX << ", " << positionY << "), "
              << "scale: " << scale << ", direction: " << direction << std::endl;
}

// Attack animation function
void Pokemon::attackAnimation() {
    std::cout << name << " performs an attack animation!" << std::endl;
}

// Take damage function
void Pokemon::takeDamage(float damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
    std::cout << name << " takes " << damage << " damage! Current HP: " << hp << std::endl;
    damageAnimation();
}

// Damage animation function
void Pokemon::damageAnimation() {
    std::cout << name << " displays a damage animation!" << std::endl;
}

// Use skill function
void Pokemon::useSkill(int skillIndex) {
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

// Render skill effect function
void Pokemon::renderSkillEffect(const Skill& skill) {
    std::cout << "Rendering effect of skill " << skill.name << std::endl;
}
