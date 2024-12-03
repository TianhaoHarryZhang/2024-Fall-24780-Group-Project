#ifndef TRAINER_H
#define TRAINER_H
#include <stdio.h>
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "People.h"
#include "Pokemon.h"
#include "Scene.h"

class Trainer : public People
{
private:
	float x, y;
	static const int grid[22][38];
	YsRawPngDecoder Trainer_png;
	bool inConversation;

public:
	Trainer(const char *name, float x = 0.0, float y = 0.0);

	int map_wid;
	int map_hei;
	int grid_size;

	bool moving;
	bool isMoving();

	int facing_direction;
	void loadTrainer_png(const char *filePath);
	void face_west();
	void face_east();
	void face_north();
	void face_south();
	void drawTrainer();

	void move_west(int map_wid, int grid_size);
	void move_east(int map_wid, int grid_size);
	void move_north(int map_hei, int grid_size);
	void move_south(int map_hei, int grid_size);

	bool isFacing(const People &person, int gridSize) const;
	void interactWith(People& otherCharacter, YsRawPngDecoder& main_scene, People& nurse, People& comp, Scene_State* scene_state);

	void displayPokemon(Trainer *trainer, Scene_State *scene_state, void *pokemon_scene, YsSoundPlayer *player, YsSoundPlayer::SoundData *sound);
	Pokemon pokemon[2] = {Pokemon("Dog", "Lv. 1", 100, 100, Skill("Bite", 10), Skill("Scratch", 8), "dog"), Pokemon("Rabbit", "Lv. 1", 80, 80, Skill("Bite", 10), Skill("Scratch", 8), "rabbit")};
	int currentPokemonIndex = 0;
};

#endif