#include <stdio.h>
#include <string.h>
#include "People.h"

class Trainer : public People
{
private:

    float x, y;
    bool needHeal;

public:

    Trainer(const char* name, float x = 0.0, float y = 0.0);
    void move(float dx, float dy);
    bool heal();
    void interactWith(People& otherCharacter);
};
