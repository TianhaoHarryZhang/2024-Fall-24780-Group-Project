#include "BattleScene.h"
#include <iostream>

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
    while (true) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int terminate = 0;
        int lb, mb, rb, mx, my;
        int exit_x, exit_y, exit_h, exit_w;
        int attack_x, attack_y, attack_h, attack_w;
        int bag_x, bag_y, bag_h, bag_w;

        FsGetMouseState(lb, mb, rb, mx, my);

        // Load battle scene here
        

        // Check if any button is pressed
        if (lb == 1) {
            if (mx > exit_x && mx < exit_x + exit_w && my > exit_y && my < exit_y + exit_h) {
                terminate = 1;
            }
            else if (mx > attack_x && mx < attack_x + attack_w && my > attack_y && my < attack_y + attack_h) {
                // Put attack animation here

            }
            else if (mx > bag_x && mx < bag_x + bag_w && my > bag_y && my < bag_y + bag_h) {
                // Put backpack scene here

            }
        }

        if (terminate == 1) {
            break;
        }

        FsSwapBuffers();
    }


    retun 0;
}