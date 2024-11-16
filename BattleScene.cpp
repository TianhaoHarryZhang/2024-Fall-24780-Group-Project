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
    PokemonUI UI;

    bool terminate = false;
    int lb, mb, rb, mx, my;
    int exit_x, exit_y, exit_h, exit_w;
    int attack1_x, attack1_y, attack2_x, attack2_y, attack_h, attack_w;
    int bag_x, bag_y, bag_h, bag_w;
    bool playerRound = true; // Player always go first
    int currentPokemon = 1; // Default Pokemon is the first pokemon
    

    while (true) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        FsGetMouseState(lb, mb, rb, mx, my);

        // Load battle scene here
        if (currentPokemon == 1) {
            UI.renderHPBar(pokemon1.hp);
        }
        else {
            UI.renderHPBar(pokemon2.hp);
        }
        


        // Check if it is player's round
        if (playerRound == true){
            // Check if any button is pressed
            if (lb == 1) {
                if (mx > exit_x && mx < exit_x + exit_w && my > exit_y && my < exit_y + exit_h) {
                    terminate = true;
                }
                // First skill
                else if (mx > attack1_x && mx < attack1_x + attack_w && my > attack1_y && my < attack1_y + attack_h) {
                    playerRound = !playerRound;
                }
                // Second skill
                else if (mx > attack2_x && mx < attack2_x + attack_w && my > attack2_y && my < attack2_y + attack_h) {
                    playerRound = !playerRound;
            }
            else if (mx > bag_x && mx < bag_x + bag_w && my > bag_y && my < bag_y + bag_h) {
                // Put backpack scene here

            }
        }
        }
        // NPC's round
        else {

        }

        if (terminate == true) {
            break;
        }

         FsSwapBuffers();
     }


     retun 0;
}