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
    std::string fname;
    float hp;
    float maxHp;

    // Skills
    Skill skill1;
    Skill skill2;

    // Constructor
    Pokemon(std::string name, std::string level, float hp, float maxHP, Skill skill1, Skill skill2, std::string fname);

    // Methods
    void render(int positionX, int positionY, float scale, int direction);
    void attackAnimation(int positionX, int positionY, float scale, int direction, int *animation_counter, bool *in_animation);
    void takeDamage(float damage);
    void useSkill(int skillIndex);
    void renderSkillEffect(const Skill& skill, int positionX, int positionY, int *skill_animation_counter, bool *in_skill_animation);

private:
    void damageAnimation();
};

#endif // POKEMON_H
