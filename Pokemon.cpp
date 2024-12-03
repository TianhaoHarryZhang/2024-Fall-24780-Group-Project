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
void Pokemon::render(int positionX, int positionY, float scale, int direction)
{
    YsRawPngDecoder pokemon_fig;
    std::string fname_total;
    if (direction == 1)
    {
        fname_total = "images/monster/" + fname + "_right.png";
    }
    else if (direction == 2)
    {
        fname_total = "images/monster/" + fname + "_left.png";
    }

    const char *cstr_fname_total = fname_total.c_str();
    if (YSOK != pokemon_fig.Decode(cstr_fname_total))
    {
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
void Pokemon::attackAnimation(int positionX, int positionY, float scale, int direction, int *animation_counter, bool *in_animation)
{
    // std::cout << name << " performs an attack animation!" << std::endl;
    if (*animation_counter < 20)
    {
        int randX = rand() % 20 - 10;
        positionX += randX;
        Pokemon::render(positionX, positionY, scale, direction);
        (*animation_counter)++;
    }
    else
    {
        *in_animation = false;
    }
}

// Take damage function
void Pokemon::takeDamage(float damage)
{
    hp -= damage;
    if (hp < 0)
        hp = 0;
    std::cout << name << " takes " << damage << " damage! Current HP: " << hp << std::endl;
    damageAnimation();
}

// Damage animation function
void Pokemon::damageAnimation()
{
    std::cout << name << " displays a damage animation (Not implemented)!" << std::endl;
}

// Use skill function
void Pokemon::useSkill(int skillIndex)
{
    if (skillIndex == 1)
    {
        std::cout << name << " uses " << skill1.name << " causing " << skill1.damage << " damage!" << std::endl;
    }
    else if (skillIndex == 2)
    {
        std::cout << name << " uses " << skill2.name << " causing " << skill2.damage << " damage!" << std::endl;
    }
    else
    {
        std::cout << "Invalid skill index." << std::endl;
    }
}

// Render skill effect function
void Pokemon::renderSkillEffect(const Skill &skill, int positionX, int positionY, int *skill_animation_counter, bool *in_skill_animation)
{
    if (skill.name == "Bite")
    {
        if (*skill_animation_counter < 20)
        {
            std::cout << "Bite effect is displayed!" << std::endl;
            YsRawPngDecoder bite_up, bite_down;
            if (YSOK != bite_up.Decode("images/BattleScene/Skills/Bite_up.png") || YSOK != bite_down.Decode("images/BattleScene/Skills/Bite_down.png"))
            {
                std::cout << "Failed to open file." << std::endl;
                return;
            }
            bite_up.Flip();
            bite_down.Flip();
            glPixelZoom(0.5, 0.5);
            positionX = positionX + 150;
            positionY = positionY - 50;
            glRasterPos2i(positionX, positionY);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawPixels(bite_up.wid, bite_up.hei, GL_RGBA, GL_UNSIGNED_BYTE, bite_up.rgba);
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);

            glRasterPos2i(positionX, positionY + 100);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawPixels(bite_down.wid, bite_down.hei, GL_RGBA, GL_UNSIGNED_BYTE, bite_down.rgba);
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);
            (*skill_animation_counter)++;
        }
        else
        {
            *in_skill_animation = false;
        }
    }
    else if (skill.name == "Scratch")
    {
        if (*skill_animation_counter < 20)
        {
            std::cout << "Scratch effect is displayed!" << std::endl;
            YsRawPngDecoder scratch;
            if (YSOK != scratch.Decode("images/BattleScene/Skills/Scratch.png"))
            {
                std::cout << "Failed to open file." << std::endl;
                return;
            }
            scratch.Flip();
            glPixelZoom(0.2, 0.2);
            positionX = positionX + 150;
            positionY = positionY - 50;
            glRasterPos2i(positionX, positionY);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDrawPixels(scratch.wid, scratch.hei, GL_RGBA, GL_UNSIGNED_BYTE, scratch.rgba);
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);
            (*skill_animation_counter)++;
        }
        else
        {
            *in_skill_animation = false;
        }
    }
    else
    {
        std::cout << "Skill effect is not implemented!" << std::endl;
    }
}

// Get HP function
int Pokemon::getHP()
{
    return hp;
}
