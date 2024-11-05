


class Message
{

public:

	bool typing_dynamic_message = false;

	int num_words_typed = 0;

	char* message_to_type = nullptr;

	void renderText(float x, float y, const char text[], int R, int G, int B);

	void print_static_message(const char message[], float start_x, float start_y, float step_x, float step_y, int width);

	void type_character(char* message_pointer, float start_x, float start_y, int start, int numChars);

	void getSubset(char* source, int m, int numChars, char* result);


};







