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

// int main() {
//     while (true) {
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         int terminate = 0;




//         FsSwapBuffers();
//     }


//     retun 0;
// }