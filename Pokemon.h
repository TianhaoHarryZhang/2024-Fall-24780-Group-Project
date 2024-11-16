#ifndef POKEMON_H
#define POKEMON_H

#include <string>

struct Skill {
    std::string name;
    float damage;

    Skill(std::string name, float damage);
};

class Pokemon {
public:
    // Attributes
    std::string name;
    std::string level;
    float hp;
    float maxHp;

    // Skills
    Skill skill1;
    Skill skill2;

    // Constructor
    Pokemon(std::string name, std::string level, float hp, Skill skill1, Skill skill2);

    // Methods
    void render(int positionX, int positionY, float scale, int direction);
    void attackAnimation();
    void takeDamage(float damage);
    void useSkill(int skillIndex);

private:
    void damageAnimation();
    void renderSkillEffect(const Skill& skill);
};

#endif // POKEMON_H
