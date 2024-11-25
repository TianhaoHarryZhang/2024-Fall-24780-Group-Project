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
    YsRawPngDecoder Bag, Fight, Pokemon, Run;
    if (YSOK != Bag.Decode("images/common/bag_box.png") or
        YSOK != Fight.Decode("images/common/fight_button.png") or
        YSOK != Pokemon.Decode("images/common/pokemon_box.png") or
        YSOK != Run.Decode("images/BattleScene/BattleScene_RunButton.png"))
    {
        printf("Failed to open file.\n");
        return;
    }
    Bag.Flip();
    Fight.Flip();
    Pokemon.Flip();
    Run.Flip();

    // glRasterPos2i(720, 500);
    // glPixelZoom(0.3, 0.3);
    // glDrawPixels(Run.wid, Run.hei, GL_RGBA, GL_UNSIGNED_BYTE, Run.rgba);

    glRasterPos2i(720, 525);
    glPixelZoom(0.3, 0.3);
    glDrawPixels(Bag.wid, Bag.hei, GL_RGBA, GL_UNSIGNED_BYTE, Bag.rgba);
    printf("Bag Width: %d Height: %d\n", Bag.wid, Bag.hei);

    glRasterPos2i(720, 610);
    glPixelZoom(0.3, 0.3);
    glDrawPixels(Fight.wid, Fight.hei, GL_RGBA, GL_UNSIGNED_BYTE, Fight.rgba);

    glRasterPos2i(720, 700 - 1);
    glPixelZoom(0.3, 0.3);
    glDrawPixels(Pokemon.wid, Pokemon.hei, GL_RGBA, GL_UNSIGNED_BYTE, Pokemon.rgba);
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
    int attack1_x, attack1_y, attack2_x, attack2_y, attack_h, attack_w; // Rendering attribute for the attack button
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

    hp_player_x = 275;
    hp_player_y = 400;
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
    bag_y = 455;
    bag_w = 386;
    bag_h = 70;

    // fight button location: 720, 610 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 610 < y < 843 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)

    // pokemon button location: 720, 700 1287*0.3, 233*0.3
    // width range 720 < x < 1106 (width of the image is 1287, ratio 0.3; 1287 * 0.3 = 386)
    // height range 700 < y < 933 (height of the image is 233, ratio 0.3; 233 * 0.3 = 70)

    // FsOpenWindow(16, 16, 1225, 700, 1);

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
        UI.renderOptions(0, 0, "images/BattleScene/BattleScene_BagButton.png");
        UI.renderTextBox("TEST MSG", 0, 0, 0, 0);

        currentPokemon->render(playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction);
        currentNPCPokemon->render(NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction);

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

                if (mx > bag_x && mx < (bag_x + bag_w) && my > bag_y && my < (bag_y + bag_h))
                {
                    printf("Bag button pressed\n");
                    *scene_state = IN_MEDICINE_POCKET;
                    break;
                }
            }
        }
        // NPC's round
        else
        {
            playerRound = !playerRound;
            currentNPCPokemon->attackAnimation();
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