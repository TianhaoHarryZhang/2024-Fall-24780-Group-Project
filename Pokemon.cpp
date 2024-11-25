#include <iostream>
#include "Pokemon.h"
#include "yspng.h"
#include "fssimplewindow.h"

// Constructor for Skill
Skill::Skill(std::string name, float damage)
    : name(name), damage(damage) {}

// Constructor for Pokemon
Pokemon::Pokemon(std::string name, std::string level, float hp, float maxHP, Skill skill1, Skill skill2, std::string fname)
    : name(name), level(level), hp(hp), maxHp(maxHP), skill1(skill1), skill2(skill2), fname(fname) {}

// Render function
void Pokemon::render(int positionX, int positionY, float scale, int direction) {
    YsRawPngDecoder pokemon_fig;
    std::string fname_total;
    if (direction == 1){
        fname_total = "images/monster/" + fname + "_right.png";
    }else if (direction == 2)
    {
        fname_total = "images/monster/" + fname + "_left.png";
    }
    
    const char* cstr_fname_total = fname_total.c_str();
    if (YSOK != pokemon_fig.Decode(cstr_fname_total)) {
        std::cout << "Failed to open file." << std::endl;
        return;
    }
    pokemon_fig.Flip();
    glPixelZoom(scale, scale);
    glRasterPos2i(positionX, positionY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawPixels(pokemon_fig.wid, pokemon_fig.hei, GL_RGBA, GL_UNSIGNED_BYTE, pokemon_fig.rgba);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
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
