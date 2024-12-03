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
    if (YSOK != Bag.Decode("images/common/bag_box.png") ||
        YSOK != Fight.Decode("images/common/fight_button.png") ||
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

void PokemonUI::renderSkillSelection(Pokemon* pokemon, int positionX1, int positionY1, int positionX2, int positionY2)
{
    YsRawPngDecoder skill1, skill2;
    if (YSOK != skill1.Decode("images/BattleScene/BattleScene_TextBox.png") ||
        YSOK != skill2.Decode("images/BattleScene/BattleScene_TextBox.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    skill1.Flip();
    skill2.Flip();
    // Render params
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
    const char* cstr_skill1 = pokemon->skill1.name.c_str();
    const char* cstr_skill2 = pokemon->skill2.name.c_str();
    int ctsr_skill1_len = strlen(cstr_skill1);
    int ctsr_skill2_len = strlen(cstr_skill2);
    float skill1_center_bias_x = (16 * ctsr_skill1_len) / 2;
    float skill2_center_bias_x = (16 * ctsr_skill2_len) / 2;
    float skill1_center_bias_y = 10;
    float skill2_center_bias_y = 10;

    messageout.renderText(int(positionX1 + (skill1.wid * ratioX1 / 2) - skill1_center_bias_x), int(positionY1 - (skill1.hei * ratioY1 / 2) + skill1_center_bias_y), cstr_skill1, 0, 0, 0);
    messageout.renderText(int(positionX2 + (skill2.wid * ratioX2 / 2) - skill2_center_bias_x), int(positionY2 - (skill2.hei * ratioY2 / 2) + skill2_center_bias_y), cstr_skill2, 0, 0, 0);

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
    float ratioX = 1.2;
    float ratioY = 0.8;
    glPixelZoom(ratioX, ratioY);
    glDrawPixels(textBox.wid, textBox.hei, GL_RGBA, GL_UNSIGNED_BYTE, textBox.rgba);

    Message messageout;
    const char *cstr_messgae = message.c_str();
    int ctsr_messgae_len = strlen(cstr_messgae);
    float center_bias_x = (16 * ctsr_messgae_len) / 2 - 10;
    float center_bias_y = 10;
    messageout.renderText(int(textBox.wid / 2 * ratioX) - center_bias_x, 700 - int(textBox.hei / 2 * ratioY) + center_bias_y, cstr_messgae, 0, 0, 0);

    // messageout.renderText(int(textBox.wid / 2 * ratioX) - 55, 700 - int(textBox.hei / 2 * ratioY) + 10, cstr_messgae, 0, 0, 0);
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

void PokemonUI::performAttack(
    Pokemon* attacker, 
    Pokemon* defender, 
    int skillNumber, 
    int attacker_x, 
    int attacker_y, 
    float attacker_scale, 
    int attacker_direction,
    int* animation_counter, 
    bool* attacker_in_animation,
    int* skill_animation_counter, 
    bool* attacker_in_skill_animation,
    bool* attacker_in_attack
    ) 
{
    attacker->attackAnimation(attacker_x, attacker_y, attacker_scale, attacker_direction, animation_counter, attacker_in_animation);
    attacker->useSkill(skillNumber);
    Skill skill = (skillNumber == 1) ? attacker->skill1 : attacker->skill2;
    attacker->renderSkillEffect(skill, attacker_x, attacker_y, skill_animation_counter, attacker_in_skill_animation);
    if (*skill_animation_counter == 1)
    {
        std::cout << "take damage" << std::endl;
        defender->takeDamage(skill.damage);
    }
    // defender->damageAnimation();
    if (*attacker_in_animation == false && *attacker_in_skill_animation == false)
    {
        *attacker_in_attack = false;
    }
}

int PokemonUI::battle(Trainer *trainer, float *NPC_pokemon_hp, Scene_State *scene_state, YsSoundPlayer *player, YsSoundPlayer::SoundData *sound)
{
    Pokemon &pokemon1 = trainer->pokemon[0];
    Pokemon &pokemon2 = trainer->pokemon[1];
    Pokemon NPCpokemon("Fox", "Lv. 1", *NPC_pokemon_hp, 100, Skill("Bite", 10), Skill("Scratch", 8), "fox");
    PokemonUI UI;

    Pokemon &currentPokemon = (*trainer).pokemon[trainer->currentPokemonIndex]; // The pokeemon that is currently selected, defalut is pokemon 1
    Pokemon &currentNPCPokemon = NPCpokemon; // The NPC's pokemon

    bool terminate = false;
    bool victory = false;
    int lb, mb, rb, mx, my;                                                     // Store the position and state of the mouse
    int pokemon_button_x, pokemon_button_y, pokemon_button_h, pokemon_button_w; // Rendering attribute for the pokemon button
    int attack_x, attack_y, attack_h, attack_w;                                 // Rendering attribute for the attack button
    int skill1_x, skill1_y, skill1_h, skill1_w;                                 // Rendering attribute for the skill1 button
    int skill2_x, skill2_y, skill2_h, skill2_w;                                 // Rendering attribute for the skill2 button
    int bag_x, bag_y, bag_h, bag_w;                                             // Rendering attribute for the backpack button
    int hp_player_x, hp_player_y, hp_player_h, hp_player_w;                     // Player pokemon's hp bar positon
    int hp_NPC_x, hp_NPC_y, hp_NPC_h, hp_NPC_w;                                 // NPC pokemon's hp bar positon
    int playerPokemon_x, playerPokemon_y, playerPokemon_direction;
    float playerPokemon_scale;                            // Player pokemon's rendering attribute
    int NPCpokemon_x, NPCpokemon_y, NPCpokemon_direction; // NPC pokemon's rendering attribute
    float NPCpokemon_scale;                               // NPC pokemon's rendering attribute
    bool playerRound = true;                              // Player always go first
    bool pokemonSelect = true;                            // Default Pokemon is the first pokemon
    int mouseEvent;                                       // Store the mouse event
    int skill;                                            // Indicate which skill will be used

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

    // skill1 button location: 720, 560, 475*0.6, 308*0.3
    // width range 720 < x < 1005 (width of the image is 475, ratio 0.6; 475 * 0.6 = 285)
    // height range 560 < y < 652 (height of the image is 308, ratio 0.3; 308 * 0.3 = 92)
    skill1_x = 720;
    skill1_y = 560;
    skill1_w = 285;
    skill1_h = 92;

    // skill2 button location: 720, 670, 475*0.6, 308*0.3
    // width range 720 < x < 1005 (width of the image is 475, ratio 0.6; 475 * 0.6 = 285)
    // height range 670 < y < 762 (height of the image is 308, ratio 0.3; 308 * 0.3 = 92)
    skill2_x = 720;
    skill2_y = 670;
    skill2_w = 285;
    skill2_h = 92;

    // FsOpenWindow(16, 16, 1225, 700, 1);
    bool user_pokemon_in_attack = false;
    bool NPC_pokemon_in_attack = false;
    bool in_skill_selection = false;
    bool user_pokemon_in_animation = false;
    bool user_pokemon_in_skill_animation = false;
    bool NPC_pokemon_in_animation = false;
    bool NPC_pokemon_in_skill_animation = false;
    
    int animation_counter = 0;
    int skill_animation_counter = 0;

    while (true)
    {
        Pokemon &currentPokemon = (*trainer).pokemon[trainer->currentPokemonIndex];
        FsPollDevice();
        if (FsInkey() == FSKEY_ESC)
        {
            exit(0);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);

        // If the pokemon is overhealed, reset hp back to maxhp
        if (currentPokemon.hp > currentPokemon.maxHp) {
            currentPokemon.hp = currentPokemon.maxHp;
        }

        // Load battle scene here
        // Render pokeemon and their hp bar

        UI.renderBK();
        UI.renderHPBar(currentPokemon.hp, currentPokemon.maxHp, hp_player_x, hp_player_y, hp_player_w, hp_player_h);
        UI.renderHPBar(currentNPCPokemon.hp, currentNPCPokemon.maxHp, hp_NPC_x, hp_NPC_y, hp_NPC_w, hp_NPC_h);
        UI.renderName(currentPokemon.name, hp_player_x, hp_player_y + hp_player_h + 30);
        UI.renderName(currentNPCPokemon.name, hp_NPC_x, hp_NPC_y + hp_NPC_h + 30);
        if (in_skill_selection)
        {
            if (user_pokemon_in_attack == false)
            {
                UI.renderTextBox("Select Option", 0, 0, 0, 0);
            }
            UI.renderSkillSelection(&currentPokemon, skill1_x, skill1_y, skill2_x, skill2_y);
        }
        else
        {
            if (user_pokemon_in_attack == false)
            {
                UI.renderTextBox("Select Skill", 0, 0, 0, 0);
            }
            UI.renderOptions(0, 0, "images/BattleScene/BattleScene_BagButton.png");
        }

        // UI.renderTextBox("TEST MSG", 0, 0, 0, 0);

        if (user_pokemon_in_attack)
        {    
            UI.renderTextBox("User Attacking", 0, 0, 0, 0);
            performAttack(
                &currentPokemon,         
                &currentNPCPokemon,            
                skill,                 
                playerPokemon_x,       
                playerPokemon_y,       
                playerPokemon_scale,   
                playerPokemon_direction, 
                &animation_counter,    
                &user_pokemon_in_animation, 
                &skill_animation_counter,   
                &user_pokemon_in_skill_animation,
                &user_pokemon_in_attack
            );
            
            // std::cout << user_pokemon_in_attack << std::endl;
            if (user_pokemon_in_attack == false)
            {
                if (skill == 1){
                    *NPC_pokemon_hp -= currentPokemon.skill1.damage;
                }
                else if (skill == 2)
                {
                    *NPC_pokemon_hp -= currentPokemon.skill2.damage;
                }
                
                playerRound = false;
            }
        }
        else {
            currentPokemon.render(playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction);
        }

        if (NPC_pokemon_in_attack)
        {    
            UI.renderTextBox("NPC Attacking", 0, 0, 0, 0);
            performAttack(
                &currentNPCPokemon,         
                &currentPokemon,            
                1,                 
                NPCpokemon_x,       
                NPCpokemon_y,       
                NPCpokemon_scale,   
                NPCpokemon_direction,       
                &animation_counter,    
                &NPC_pokemon_in_animation, 
                &skill_animation_counter,   
                &NPC_pokemon_in_skill_animation,
                &NPC_pokemon_in_attack
            );
            if (NPC_pokemon_in_attack == false)
            {
                playerRound = true;
            }
        }
        else {
            currentNPCPokemon.render(NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction);
        }

        // Check if it is player's round
        if (playerRound == true)
        {
            std::cout << "Player's round" << std::endl;
            if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN)
            {
                printf("Button pressed at %d %d\n", mx, my);
                // check if the user is in skill selection first
                if (in_skill_selection == false) {
                    if (mx > bag_x && mx < (bag_x + bag_w) && my < bag_y && my >(bag_y - bag_h)) // bag button pressed
                    {
                        printf("Bag button pressed\n");
                        *scene_state = IN_MEDICINE_POCKET;
                        // play sound
                        player->PlayOneShot(*sound);
                        break;
                    }
                    else if (mx > pokemon_button_x && mx < (pokemon_button_x + pokemon_button_w) && my < pokemon_button_y && my >(pokemon_button_y - pokemon_button_h)) // change pokemon button pressed
                    {
                        printf("Pokemon button pressed\n");
                        *scene_state = IN_ANIMAL_POCKET;
                        // play sound
                        player->PlayOneShot(*sound);
                        break;
                    }
                    else if ((mx > attack_x && mx < (attack_x + attack_w) && my < attack_y && my >(attack_y - attack_h))) // attack button pressed
                    {
                        std::cout << "Attack button pressed" << std::endl;
                        // Attack button pressed, switch to skill selection
                        in_skill_selection = true;
                        // play sound
                        player->PlayOneShot(*sound);
                    }
                }
                else
                {
                    player->PlayOneShot(*sound);              
                    // Check which skill is selected
                    if (mx > skill1_x && mx < (skill1_x + skill1_w) && my < skill1_y && my >(skill1_y - skill1_h)) 
                    {
                        skill = 1;
                        user_pokemon_in_attack = true;
                        animation_counter = 0;
                        skill_animation_counter = 0;
                        user_pokemon_in_animation = true;
                        user_pokemon_in_skill_animation = true;

                        in_skill_selection = false;
                    } else if (mx > skill2_x && mx < (skill2_x + skill2_w) && my < skill2_y && my >(skill2_y - skill2_h))
                    {
                        skill = 2;
                        user_pokemon_in_attack = true;
                        animation_counter = 0;
                        skill_animation_counter = 0;
                        user_pokemon_in_animation = true;
                        user_pokemon_in_skill_animation = true;

                        in_skill_selection = false;
                    }
                }
            }
        }
        // NPC's round
        else
        {    
            std::cout << "NPC's round" << std::endl;
            playerRound = !playerRound;
            NPC_pokemon_in_attack = true;
            animation_counter = 0;
            skill_animation_counter = 0;
            NPC_pokemon_in_animation = true;
            NPC_pokemon_in_skill_animation = true;
        }

        // Check if any of the pokemons are out of hp
        if (currentNPCPokemon.hp <= 0)
        {
            // NPC out of pokemon, victory
            terminate = true;
            victory = true;
        }
        else if (pokemon1.hp <= 0 && pokemon2.hp <= 0)
        {
            std::cout << "Defeat" << std::endl;
            // Player out of pokemons, defeat
            terminate = true;
        } 
        else if (pokemon1.hp <= 0)
        {
            trainer->currentPokemonIndex = 1;
        }
        else if (pokemon2.hp <= 0)
        {
            trainer->currentPokemonIndex = 0;
        }

        if (terminate)
        {
            *scene_state = IN_MAIN_SCENE;
            break;
        }
        FsSwapBuffers();
    }

    return 0;
}
