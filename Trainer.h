#include <stdio.h>
#include <string.h>
#include "People.h"
#include "yspng.h"

class Trainer : public People
{
private:

    float x, y;
    YsRawPngDecoder Trainer_png;

public:

    Trainer(const char* name, float x = 0.0, float y = 0.0);
    bool isMoving;
    int facing_direction;

    void loadTrainer_png(const char* filePath);
    void face_west();
    void face_east();
    void face_north();
    void face_south();
    void drawTrainer();

    void move_west();
    void move_east();
    void move_north();
    void move_south();

    bool needHeal;

    void interactWith(People& otherCharacter);
};
