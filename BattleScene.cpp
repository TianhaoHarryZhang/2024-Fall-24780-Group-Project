#include "BattleScene.h"
#include <iostream>
#include "Pokemon.h"

void PokemonUI::renderHPBar(float hp, float maxHp, int positionX, int positionY, int width, int height) {
    // Calculate HP percentage
    float hpPercent = (hp / maxHp) * 100;
    std::cout << "Rendering HP bar at (" << positionX << ", " << positionY << ") with width " << width
              << " and height " << height << ". HP: " << hp << "/" << maxHp << " (" << hpPercent << "%)" << std::endl;
}

void PokemonUI::renderOptions(int positionX, int positionY) {
    // Display basic options for Pokémon battle
    std::cout << "Rendering battle options at (" << positionX << ", " << positionY << "):\n";
    std::cout << "[1] Fight  [2] Bag  [3] Run\n";
}

void PokemonUI::renderTextBox(const std::string& message, int positionX, int positionY, int width, int height) {
    // Render a text box with the given message
    std::cout << "Rendering text box at (" << positionX << ", " << positionY << ") with width " << width
              << " and height " << height << ".\n";
    std::cout << "Message: " << message << std::endl;
}

int main() {
    Pokemon pokemon1;
    Pokemon pokemon2;
    Pokemon NPCpokemon;
    PokemonUI UI;

    Pokemon* currentPokemon = &pokemon1; // The pokeemon that is currently selected, defalut is pokemon 1
    bool terminate = false;
    int lb, mb, rb, mx, my; // Store the position and state of the mouse
    int exit_x, exit_y, exit_h, exit_w; // Rendering attribute for the exit button
    int attack1_x, attack1_y, attack2_x, attack2_y, attack_h, attack_w; // Rendering attribute for the attack button
    int bag_x, bag_y, bag_h, bag_w; // Rendering attribute for the backpack button
    int hp_player_x, hp_player_y, hp_player_h, hp_player_w; // Player pokemon's hp bar positon
    int hp_NPC_x, hp_NPC_y, hp_NPC_h, hp_NPC_w; // NPC pokemon's hp bar positon
    int playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction; // Player pokemon's rendering attribute
    int NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction; // NPC pokemon's rendering attribute
    bool playerRound = true; // Player always go first
    int pokemonSelect = 1; // Default Pokemon is the first pokemon
    

    while (true) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        FsGetMouseState(lb, mb, rb, mx, my);

        // Load battle scene here
        // Render pokeemon and their hp bar
        UI.renderHPBar(currentPokemon->hp, currentPokemon->maxHp, hp_player_x, hp_player_y, hp_player_h, hp_player_w);
        currentPokemon->render(playerPokemon_x, playerPokemon_y, playerPokemon_scale, playerPokemon_direction);
        UI.renderHPBar(NPCpokemon.hp, NPCpokemon.maxHp, hp_NPC_x, hp_NPC_y, hp_NPC_h, hp_NPC_w)
        NPCpokemon.render(NPCpokemon_x, NPCpokemon_y, NPCpokemon_scale, NPCpokemon_direction);

        // Check if it is player's round
        if (playerRound == true){
            // Check if any button is pressed
            if (lb == 1) {
                // Exit button pressed
                if (mx > exit_x && mx < exit_x + exit_w && my > exit_y && my < exit_y + exit_h) {
                    terminate = true;
                }
                // First skill pressed
                else if (mx > attack1_x && mx < attack1_x + attack_w && my > attack1_y && my < attack1_y + attack_h) {
                    playerRound = !playerRound; // Flip the round to NPC
                    currentPokemon->attackAnimation();
                }
                // Second skill pressed
                else if (mx > attack2_x && mx < attack2_x + attack_w && my > attack2_y && my < attack2_y + attack_h) {
                    playerRound = !playerRound; // Flip the round to NPC
                    currentPokemon->attackAnimation();
            }
                // Backpack pressed
            else if (mx > bag_x && mx < bag_x + bag_w && my > bag_y && my < bag_y + bag_h) {

            }
        }
        }
        // NPC's round
        else {

        }

        if (terminate == true) {
            break;
        }

        // Check the position of the 
        if (pokemonSelect == 1) {
            currentPokemon = &pokemon1;
        }
        else {
            currentPokemon = &pokemon2;
        }

         FsSwapBuffers();
     }


     retun 0;
}