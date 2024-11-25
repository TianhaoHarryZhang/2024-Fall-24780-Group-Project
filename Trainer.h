#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "People.h"
#include "Pokemon.h"
class Trainer : public People
{
private:
	float x, y;
	bool needHeal;
	Pokemon pokemon[2] = {Pokemon("Dog", "Lv. 1", 100, 100, Skill("Bite", 10), Skill("Scratch", 8), "dog"), Pokemon("Rabbit", "Lv. 1", 80, 80, Skill("Bite", 10), Skill("Scratch", 8), "rabbit")};

public:
	Trainer(const char *name, float x = 0.0, float y = 0.0);
	void move(float dx, float dy);
	bool heal();
	void interactWith(People &otherCharacter);
	void displayPokemon(void *pokemon_scene);
};