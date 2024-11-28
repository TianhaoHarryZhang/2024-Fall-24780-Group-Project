#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H
#include "yssimplesound.h"
#include "Scene.h"
#include "Pokemon.h"
#include <string>

class PokemonUI
{
public:
    // Renders the HP bar for a Pokémon
    void renderHPBar(float hp, float maxHp, int positionX, int positionY, int width, int height);

    // Renders the options for a Pokémon battle, like "Fight," "Bag," "Run," etc.
    void renderOptions(int positionX, int positionY, std::string filename);

    // Renders a text box to display messages, e.g., "Charizard used Fire Blast!"
    void renderTextBox(const std::string &message, int positionX, int positionY, int width, int height);

    void renderName(std::string name, int positionX, int positionY);

    void renderBK();

    void renderSkillSelection(Pokemon *pokemon);

    int battle(Scene_State *scene_state, YsSoundPlayer *player, YsSoundPlayer::SoundData *sound);
};

#endif
