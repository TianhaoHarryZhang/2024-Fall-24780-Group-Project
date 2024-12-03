#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
#include "ysglfontdata.h"
#include "utility.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "Scene.h"
#include "yssimplesound.h"


void battle_start (void)
{
    YsRawPngDecoder bg, user, computer;

    int n = 0;

    float user_x = 910.f;
    float computer_x = 50.f;
    float v = 5.f;

    if (YSOK != bg.Decode("images/battle_start/fight_bg.png") || YSOK != user.Decode("images/battle_start/fight_user.png") || YSOK != computer.Decode("images/battle_start/fight_computer.png"))
    {
        printf("Failed to open image files.\n");
        //*scene_state = IN_MAIN_SCENE;
        return;
    }
    else
    {
        bg.Flip();
        user.Flip();
        computer.Flip();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (;;)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (FsInkey() == FSKEY_ESC)
        {
            exit(0);
        }
 

        //display computer trainer image
        glRasterPos2d(computer_x, (double)(610.f));
        
        glDrawPixels(computer.wid, computer.hei, GL_RGBA, GL_UNSIGNED_BYTE, computer.rgba);
        


        //display user trainer image
        glRasterPos2d(user_x, (double)(610.f));
        glDrawPixels(user.wid, user.hei, GL_RGBA, GL_UNSIGNED_BYTE, user.rgba);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //display battle-starting background image
        glRasterPos2d(130.0, (double)(620));
        glDrawPixels(bg.wid, bg.hei, GL_RGBA, GL_UNSIGNED_BYTE, bg.rgba);


        FsSwapBuffers();

        if (n==30) //
        {
            FsSleep(16000);
            break;
        }

        n += 1;
        user_x -= v;
        computer_x += v;

        FsSleep(10);
    }

    return;


}


void game_loading (Scene_State* scene_state)
{

    YsRawPngDecoder loading_image, running_trainer;

	if (YSOK != loading_image.Decode("images/loading/Loading.png") || YSOK != running_trainer.Decode("images/loading/running_trainer.png"))
    {
        printf("Failed to open game-loading image files.\n");
        *scene_state = IN_MAIN_SCENE;
        return;
    }
    else
    {
    	loading_image.Flip();
    	running_trainer.Flip();
    }


    int n = 0;

    float x = 5.f;

    for (;;)
    {
    	FsPollDevice();
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    	if (FsInkey() == FSKEY_ESC)
        {
            break;
        }

    	//display game-loading temporary image
		glRasterPos2d(0.0, (double)(loading_image.hei - 1));
		glDrawPixels(loading_image.wid, loading_image.hei, GL_RGBA, GL_UNSIGNED_BYTE, loading_image.rgba);


		//display a white progress bar
    	glColor3f(1.0f, 1.0f, 1.0f);
    	// Window size: Wid 1225 Hei 700
    	glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.f, 700.f); // Bottom-left corner
        glVertex2f(1225.f, 700.f); // Bottom-right corner
        glVertex2f(0.f, 650.f); // Top-left corner
        glVertex2f(1225.f, 650.f); // Top-right corner
    	glEnd();
    	glFlush(); 


    	//display running trainer image
		glRasterPos2d(x, (double)(695.f));
		glDrawPixels(running_trainer.wid, running_trainer.hei, GL_RGBA, GL_UNSIGNED_BYTE, running_trainer.rgba);



		//display a green progress bar of completion
    	glColor3f(0.f, 1.0f, 0.f);
    	// Window size: Wid 1225 Hei 700
    	glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.f, 700.f); // Bottom-left corner
        glVertex2f(x, 700.f); // Bottom-right corner
        glVertex2f(0.f, 650.f); // Top-left corner
        glVertex2f(x, 650.f); // Top-right corner
    	glEnd();
    	glFlush(); // Ensure all commands are executed


    	FsSwapBuffers();

    	if (n==2000) //
    	{
    		break;
    	}

    	n += 1;
    	x += 0.605f;
    }

    *scene_state = IN_MAIN_SCENE;

	return;
}



void generate_number_png(int number, int width, int height, int font_size, int R, int G, int B, char* filename)
{
	char command[50];

	snprintf(command, sizeof(command), "python number.py %d %d %d %d %d %d %d %s", number, width, height, font_size, R, G, B, filename);

    system(command);
}

//void load_sound(YsSoundPlayer::SoundData &sound, const char *filename) {
//    if(YSOK!=sound.LoadWav(filename))
//    {
//        std::cout << "Error!  Cannot load file: " << filename << std::endl;
//    }
//}

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
    std::vector<char> characters_to_type(numChars + 1);
    getSubset(message_pointer, start, numChars, characters_to_type.data());

    renderText(start_x, start_y, characters_to_type.data(), 0, 0, 0);
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

