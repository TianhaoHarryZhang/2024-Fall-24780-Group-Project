#include "Scene.h"
#include "yssimplesound.h"

void generate_number_png(int number, int width, int height, int font_size, int R, int G, int B, char *filename);

void game_loading(Scene_State *scene_state);

void battle_start (void);

void battle_finish(bool UserWin);

class Message
{

public:
	bool typing_dynamic_message = false;

	int num_words_typed = 0;

	char *message_to_type = nullptr;

	void renderText(float x, float y, const char text[], int R, int G, int B);

	void print_static_message(const char message[], float start_x, float start_y, float step_x, float step_y, int width);

	void type_character(char *message_pointer, float start_x, float start_y, int start, int numChars);

	void getSubset(char *source, int m, int numChars, char *result);
};

void load_sound(YsSoundPlayer::SoundData &sound, const char *filename);
