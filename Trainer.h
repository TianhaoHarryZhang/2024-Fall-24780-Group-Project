#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "People.h"
#include "Pokemon.h"

class Trainer : public People
{
private:

    float x, y;
    static const int grid[22][38];
    YsRawPngDecoder Trainer_png;
    bool inConversation;
    Pokemon pokemon[2] = {Pokemon("Dog", "Lv. 1", 100, 100, Skill("Bite", 10), Skill("Scratch", 8), "dog"), Pokemon("Rabbit", "Lv. 1", 80, 80, Skill("Bite", 10), Skill("Scratch", 8), "rabbit")};

public:

    int map_wid;
    int map_hei;
    int grid_size;

    Trainer(const char* name, float x = 0.0, float y = 0.0);
    bool moving;
    bool isMoving();

    int facing_direction;
    void loadTrainer_png(const char* filePath);
    void face_west();
    void face_east();
    void face_north();
    void face_south();
    void drawTrainer();

    void move_west(int map_wid, int grid_size);
    void move_east(int map_wid, int grid_size);
    void move_north(int map_hei, int grid_size);
    void move_south(int map_hei, int grid_size);

    bool needHeal;
    bool heal();

    void interactWith(People& otherCharacter);

    void displayPokemon(void *pokemon_scene);
};