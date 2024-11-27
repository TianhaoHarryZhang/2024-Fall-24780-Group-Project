#include "BattleScene.h"
#include <iostream>
#include <cmath>
#include "Pokemon.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "Utility.h"

void PokemonUI::renderHPBar(float hp, float maxHp, int positionX, int positionY, int width, int height)
{
    float hpPercent = (hp / maxHp) * 100;

    // Determine the width of the filled portion of the HP bar
    int filledWidth = static_cast<int>(round((hp / maxHp) * width));

    // Set colors for the HP bar (green for high HP, yellow for medium, red for low)
    if (hpPercent > 50)
    {
        glColor3f(0.0f, 1.0f, 0.0f); // Green
    }
    else if (hpPercent > 20)
    {
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    }
    else
    {
        glColor3f(1.0f, 0.0f, 0.0f); // Red
    }

    // Draw the filled portion of the HP bar
    glBegin(GL_QUADS);
    glVertex2i(positionX, positionY);
    glVertex2i(positionX + filledWidth, positionY);
    glVertex2i(positionX + filledWidth, positionY + height);
    glVertex2i(positionX, positionY + height);
    glEnd();

    // Draw the border of the HP bar (black color)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(positionX, positionY);
    glVertex2i(positionX + width, positionY);
    glVertex2i(positionX + width, positionY + height);
    glVertex2i(positionX, positionY + height);
    glEnd();
}

void PokemonUI::renderOptions(int positionX, int positionY, std::string filename)
{
    // Display basic options for Pokémon battle
    YsRawPngDecoder Bag, Fight, Pokemon;
    if (YSOK != Bag.Decode("images/common/bag_box.png") or
        YSOK != Fight.Decode("images/common/fight_button.png") or
        YSOK != Pokemon.Decode("images/common/pokemon_box.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    Bag.Flip();
    Fight.Flip();
    Pokemon.Flip();

    glRasterPos2i(720, 525);
    glPixelZoom(0.3, 0.3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawPixels(Bag.wid, Bag.hei, GL_RGBA, GL_UNSIGNED_BYTE, Bag.rgba);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glRasterPos2i(720, 610);
    glPixelZoom(0.3, 0.3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawPixels(Fight.wid, Fight.hei, GL_RGBA, GL_UNSIGNED_BYTE, Fight.rgba);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glRasterPos2i(720, 700 - 1);
    glPixelZoom(0.3, 0.3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawPixels(Pokemon.wid, Pokemon.hei, GL_RGBA, GL_UNSIGNED_BYTE, Pokemon.rgba);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void PokemonUI::renderSkillSelection(Pokemon *pokemon)
{
    YsRawPngDecoder skill1, skill2;
    if (YSOK != skill1.Decode("images/BattleScene/BattleScene_TextBox.png") or
        YSOK != skill2.Decode("images/BattleScene/BattleScene_TextBox.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    skill1.Flip();
    skill2.Flip();
    // Render params
    int positionX1 = 720;
    int positionY1 = 560;
    int positionX2 = 720;
    int positionY2 = 670;
    float ratioX1 = 0.6;
    float ratioY1 = 0.3;
    float ratioX2 = 0.6;
    float ratioY2 = 0.3;

    // Render skill 1
    glRasterPos2i(positionX1, positionY1);
    glPixelZoom(ratioX1, ratioY1);
    glDrawPixels(skill1.wid, skill1.hei, GL_RGBA, GL_UNSIGNED_BYTE, skill1.rgba);
    // Render skill 2
    glRasterPos2i(positionX2, positionY2);
    glPixelZoom(ratioX2, ratioY2);
    glDrawPixels(skill2.wid, skill2.hei, GL_RGBA, GL_UNSIGNED_BYTE, skill2.rgba);

    // Display the skills of the Pokémon
    Message messageout;
    const char *cstr_skill1 = pokemon->skill1.name.c_str();
    const char *cstr_skill2 = pokemon->skill2.name.c_str();
    int ctsr_skill1_len = strlen(cstr_skill1);
    int ctsr_skill2_len = strlen(cstr_skill2);
    float skill1_center_bias_x = (16 * ctsr_skill1_len) / 2;
    float skill2_center_bias_x = (16 * ctsr_skill2_len) / 2;
    float skill1_center_bias_y = 10; 
    float skill2_center_bias_y = 10;

    messageout.renderText(int(positionX1 + (skill1.wid*ratioX1/2) - skill1_center_bias_x), int(positionY1 - (skill1.hei*ratioY1/2) + skill1_center_bias_y), cstr_skill1, 0, 0, 0);
    messageout.renderText(int(positionX2 + (skill2.wid*ratioX2/2) - skill2_center_bias_x), int(positionY2 - (skill2.hei*ratioY2/2) + skill2_center_bias_y), cstr_skill2, 0, 0, 0);

}

void PokemonUI::renderTextBox(const std::string &message, int positionX, int positionY, int width, int height)
{
    // Render a text box with the given message
    YsRawPngDecoder textBox;
    if (YSOK != textBox.Decode("images/BattleScene/BattleScene_TextBox.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    textBox.Flip();
    glRasterPos2i(10, 700 - 1);
    float ratioX = 0.8;
    float ratioY = 0.8;
    glPixelZoom(ratioX, ratioY);
    glDrawPixels(textBox.wid, textBox.hei, GL_RGBA, GL_UNSIGNED_BYTE, textBox.rgba);

    Message messageout;
    const char *cstr_messgae = message.c_str();
    messageout.renderText(int(textBox.wid / 2 * ratioX) - 55, 700 - int(textBox.hei / 2 * ratioY) + 10, cstr_messgae, 0, 0, 0);
}

void PokemonUI::renderName(std::string name, int positionX, int positionY)
{
    // Render the name of the Pokémon
    Message messageout;
    const char *cstr_name = name.c_str();
    messageout.renderText(positionX, positionY, cstr_name, 0, 0, 0);
}

void PokemonUI::renderBK()
{
    YsRawPngDecoder bk;
    if (YSOK != bk.Decode("images/battle_scene_new.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    bk.Flip();
    float scalingX = 2.0;
    float scalingY = 1.7;
    glRasterPos2i(0, bk.hei * scalingY - 1);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPixelZoom(scalingX, scalingY);
    glDrawPixels(bk.wid, bk.hei, GL_RGBA, GL_UNSIGNED_BYTE, bk.rgba);
}

int PokemonUI::battle(Scene_State *scene_state)
{
    //  Pokemon(std::string name, std::string level, float hp, Skill skill1, Skill skill2);
    Pokemon pokemon1("Dog", "Lv. 1", 100, 100, Skill("Bite", 10), Skill("Scratch", 8), "dog");
    Pokemon pokemon2("Fox", "Lv. 1", 100, 100, Skill("Bite", 10), Skill("Scratch", 8), "fox");
    Pokemon NPCpokemon("Rabbit", "Lv. 1", 80, 80, Skill("Bite", 10), Skill("Scratch", 8), "rabbit");
    PokemonUI UI;

    Pokemon *currentPokemon = &pokemon1;      // The pokeemon that is currently selected, defalut is pokemon 1
    Pokemon *currentNPCPokemon = &NPCpokemon; // The NPC's pokemon

    bool terminate = false;
    bool victory = false;
    int lb, mb, rb, mx, my;                                             // Store the position and state of the mouse
    int exit_x, exit_y, exit_h, exit_w;                                 // Rendering attribute for the exit button
    int pokemon_button_x, pokemon_button_y, pokemon_button_h, pokemon_button_w; // Rendering attribute for the pokemon button
    int attack_x, attack_y, attack_h, attack_w; // Rendering attribute for the attack button
    int skill1_x, skill1_y, skill1_h, skill1_w; // Rendering attribute for the skill1 button
    int skill2_x, skill2_y, skill2_h, skill2_w; // Rendering attribute for the skill2 button
    int bag_x, bag_y, bag_h, bag_w;                                     // Rendering attribute for the backpack button
    int hp_player_x, hp_player_y, hp_player_h, hp_player_w;             // Player pokemon's hp bar positon
    int hp_NPC_x, hp_NPC_y, hp_NPC_h, hp_NPC_w;                         // NPC pokemon's hp bar positon
    int playerPokemon_x, playerPokemon_y, playerPokemon_direction;
    float playerPokemon_scale;                            // Player pokemon's rendering attribute
    int NPCpokemon_x, NPCpokemon_y, NPCpokemon_direction; // NPC pokemon's rendering attribute
    float NPCpokemon_scale;                               // NPC pokemon's rendering attribute
    bool playerRound = true;                              // Player always go first
    bool pokemonSelect = true;                            // Default Pokemon is the first pokemon
    int mouseEvent;                                       // Store the mouse event

    hp_player_x = 255;
    hp_player_y = 375;
    hp_player_h = 10;
    hp_player_w = 150;

    // Poekmon loacation
    playerPokemon_x = hp_player_x;
    playerPokemon_y = hp_player_y;
    playerPokemon_scale = 0.8;
    playerPokemon_direction = 1;

    hp_NPC_x = 800;
    hp_NPC_y = 275;
    hp_NPC_h = 10;
    hp_NPC_w = 150;

    NPCpokemon_x = hp_NPC_x;
    NPCpokemon_y = hp_NPC_y;
    NPCpokemon_scale = 0.8;
    NPCpokemon_direction = 2;

    // bag button location: 720, 525 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 455 < y < 525  (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)
    bag_x = 720;
    bag_y = 525;
    bag_w = 386;
    bag_h = 70;

    // Fight button location: 720, 610 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 540 < y <610 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)
    attack_x = 720;
    attack_y = 610;
    attack_w = 386;
    attack_h = 70;

    // Pokemon button location: 720, 699
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 629 < y < 699 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)
    pokemon_button_x = 720;
    pokemon_button_y = 699;
    pokemon_button_w = 386;
    pokemon_button_h = 70;

    // fight button location: 720, 610 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 610 < y < 843 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)

    // pokemon button location: 720, 700 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 700 < y < 933 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)

    // FsOpenWindow(16, 16, 1225, 700, 1);
    bool in_skill_selection = false;
    bool skill_selected = false;
    bool user_pokemon_in_animation = false;
    bool NPC_pokemon_in_animation = false;
    bool user_pokemon_in_skill_animation = false;
    bool NPC_pokemon_in_skill_animation = false;

    int animation_counter = 0;
    int skill_animation_counter = 0;

    while (true)
    {
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

        // Load battle scene here
        // Render pokeemon and their hp bar

        UI.renderBK();
        UI.renderHPBar(currentPokemon->hp, currentPokemon->maxHp, hp_player_x, hp_player_y, hp_player_w, hp_player_h);
        UI.renderHPBar(currentNPCPokemon->hp, currentNPCPokemon->maxHp, hp_NPC_x, hp_NPC_y, hp_NPC_w, hp_NPC_h);
        UI.renderName(currentPokemon->name, hp_player_x, hp_player_y + hp_player_h + 30);
        UI.renderName(currentNPCPokemon->name, hp_NPC_x, hp_NPC_y + hp_NPC_h + 30);
        if (in_skill_selection)
        {
            UI.renderSkillSelection(currentPokemon);
        }
        else
        {
            UI.renderOptions(0, 0, "images/BattleScene/BattleScene_BagButton.png");
        }
        // UI.renderOptions(0, 0, "images/BattleScene/BattleScene_BagButton.png");
        UI.renderTextBox("TEST MSG", 0, 0, 0, 0);

        if (user_pokemon_in_animation)
        {
            currentPokemon->attackAnimation(playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction, &animation_counter, &user_pokemon_in_animation);
        } else {
            currentPokemon->render(playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction);
        }

        if (NPC_pokemon_in_animation)
        {
            currentNPCPokemon->attackAnimation(NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction, &animation_counter, &NPC_pokemon_in_animation);
        } else {
            currentNPCPokemon->render(NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction);
        }

        if (user_pokemon_in_skill_animation){
            // TODO Should know which skill is selected, now default to skill1
            currentPokemon->renderSkillEffect(currentPokemon->skill2, playerPokemon_x, playerPokemon_y, &skill_animation_counter, &user_pokemon_in_skill_animation);
        }
        if (NPC_pokemon_in_skill_animation){
            // TODO Should know which skill is selected, now default to skill1
            currentNPCPokemon->renderSkillEffect(currentNPCPokemon->skill1, NPCpokemon_x, NPCpokemon_y, &skill_animation_counter, &NPC_pokemon_in_skill_animation);
        }

        // Check if it is player's round
        if (playerRound == true)
        {
            // Check if any button is pressed
            // if (lb == 1)
            // {
            //     // Exit button pressed
            //     if (mx > exit_x && mx < exit_x + exit_w && my > exit_y && my < exit_y + exit_h)
            //     {
            //         terminate = true;
            //     }
            //     // First skill pressed
            //     else if (mx > attack1_x && mx < attack1_x + attack_w && my > attack1_y && my < attack1_y + attack_h)
            //     {
            //         playerRound = !playerRound; // Flip the round to NPC
            //         currentPokemon->attackAnimation();
            //         currentPokemon->useSkill(1);
            //         currentNPCPokemon->takeDamage(currentPokemon->skill1.damage);
            //     }
            //     // Second skill pressed
            //     else if (mx > attack2_x && mx < attack2_x + attack_w && my > attack2_y && my < attack2_y + attack_h)
            //     {
            //         playerRound = !playerRound; // Flip the round to NPC
            //         currentPokemon->attackAnimation();
            //         currentPokemon->useSkill(2);
            //         currentNPCPokemon->takeDamage(currentPokemon->skill2.damage);
            //     }
            //     // Backpack pressed
            //     else if (mx > bag_x && mx < bag_x + bag_w && my > bag_y && my < bag_y + bag_h)
            //     {
            //         printf("Bag button pressed\n");
            //     }
            // }
            if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN)
            {
                printf("Button pressed at %d %d\n", mx, my);

                if (mx > bag_x && mx < (bag_x + bag_w) && my < bag_y && my > (bag_y - bag_h))
                {
                    printf("Bag button pressed\n");
                    *scene_state = IN_MEDICINE_POCKET;
                    break;
                }
                if (mx > pokemon_button_x && mx < (pokemon_button_x + pokemon_button_w) && my < pokemon_button_y && my > (pokemon_button_y - pokemon_button_h))
                {
                    printf("Pokemon button pressed\n");
                    *scene_state = IN_ANIMAL_POCKET;
                    break;
                }
                if (in_skill_selection == false && (mx > attack_x && mx < (attack_x + attack_w) && my < attack_y && my > (attack_y - attack_h)))
                {
                    std::cout << "Attack button pressed" << std::endl;
                    // Attack button pressed, switch to skill selection
                    in_skill_selection = true;        
                }
                if (in_skill_selection == true)
                {
                    user_pokemon_in_animation = true;
                    user_pokemon_in_skill_animation = true;
                    // currentPokemon->useSkill(1);
                    // TODO: Check if the skill is selected, if selected, conduct skill animation change in_skill_slertion to false
                }
            }
        }
        // NPC's round
        else
        {
            playerRound = !playerRound;
            NPC_pokemon_in_animation = true;
            currentPokemon->takeDamage(currentNPCPokemon->skill1.damage);
        }

        if (terminate == true)
        {
            break;
        }

        // Check if any of the pokemons are out of hp
        if (currentNPCPokemon->hp == 0)
        {
            // NPC out of pokemon, victory
            terminate = true;
            victory = true;
        }
        else if (pokemon1.hp == 0 && pokemon2.hp == 0)
        {
            // Player out of pokemons, defeat
            terminate = true;
        }
        else if (pokemon1.hp == 0 || pokemon2.hp == 0)
        {
            // One of player's pokemon is out of hp, change to the other pokemon
            pokemonSelect = !pokemonSelect;
        }

        // Check the current pokemon selection
        if (pokemonSelect == true)
        {
            currentPokemon = &pokemon1;
        }
        else
        {
            currentPokemon = &pokemon2;
        }

        FsSwapBuffers();
    }

    return 0;
}