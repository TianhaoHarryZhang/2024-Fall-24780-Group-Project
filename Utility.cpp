#include <iostream>
#include "ysglfontdata.h"
#include "utility.h"
#include "fssimplewindow.h"

//render text message
void Message::renderText(float x, float y, const char text[], int R, int G, int B){

	glColor3ub(R, G, B);

    glRasterPos2f(x, y);  

    YsGlDrawFontBitmap16x20(text);
}

//print a block of message, statically. All letters printed in one frame
void Message::print_static_message(const char message[], float start_x, float start_y, float step_x, float step_y, int width)
	{
		float x = start_x;
		float y = start_y;

		int count = 0;

		for (int i = 0; message[i]!='\0'; i++)
		{
			
			if (i>1 && message[i-1]==' ')
				x -= 5.f;

			char tempStr[2] = {message[i], '\0'};
			renderText(x, y, tempStr, 0,0,0);
			
			x += step_x;

			if (count>width && message[i] == ' ')
			{
				y += step_y;
				x = start_x;

				count = 0;
			}

			count += 1;
		}

		
	}


//used to dynamically type messages with one letter being printed per frame
void Message::type_character(char* message_pointer, float start_x, float start_y, int start, int numChars)
	{
	
		char characters_to_type[numChars+1];

		getSubset(message_pointer, start, numChars, characters_to_type);

		const char* const_characters_to_type = characters_to_type;

		renderText(start_x, start_y, const_characters_to_type, 0,0,0);

		return;
		
	}


//get a subset of message string. Used for typing message, dynamically.
void Message::getSubset(char* source, int m, int numChars, char* result)
{

	int length = std::strlen(source); 
    
    if (m < 0 || m >= length || numChars < 0 || (m + numChars) > length) {
        std::cerr << "Invalid index or insufficient space in result!" << std::endl;
        result[0] = '\0';  // Set result to an empty string on failure
        return;
    }
    
    // Copy the substring from source starting at index m for numChars length
    std::strncpy(result, source + m, numChars);
    
    // Add null terminator to the end of the substring
    result[numChars] = '\0';
}


