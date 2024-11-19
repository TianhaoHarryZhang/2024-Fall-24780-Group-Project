#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "utility.h"
#include "Trainer.h"



enum Scene_State
{
	IN_MAIN_SCENE,

    IN_BATTLE_SCENE,

    IN_ANIMAL_POCKET,

    IN_MEDICINE_POCKET,

    TRANSIT_FROM_MAIN_TO_BATTLE,

    TRANSIT_FROM_BATTLE_TO_MAIN,

    TRANSIT_FROM_BATTLE_TO_ANIMAL_POCKET,

    TRANSIT_FROM_BATTLE_TO_MEDICINE_POCKET,

    TRANSIT_FROM_MAIN_TO_ANIMAL_POCKET,

    TRANSIT_FROM_MAIN_TO_MEDICINE_POCKET
};


int main(void)
{
	FsChangeToProgramDir();

	YsRawPngDecoder main_scene;

	Trainer trainer("Brock", 100, 100);

	Message message;

	Scene_State scene_state = IN_MAIN_SCENE;


	if(YSOK==main_scene.Decode("images/main_scene.png"))
    {
		printf("Wid %d Hei %d\n",main_scene.wid,main_scene.hei);
	}
	else
	{
		printf("Failed to open file.\n");
		return 1;
	}




	FsOpenWindow(0,0,800,800,1);

	for(;;)
	{
		FsPollDevice();

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		auto key = FsInkey();

		if(FSKEY_ESC==key)
		{
			break;
		}


		switch (scene_state) {

		        case IN_MAIN_SCENE:

		        	//draw the background image
		        	glRasterPos2i(0,main_scene.hei-1);
					glDrawPixels(main_scene.wid, main_scene.hei, GL_RGBA, GL_UNSIGNED_BYTE, main_scene.rgba);

		        	//move the trainer
		        	if (trainer.isMoving == true)
		        	{
		        		if(key == FSKEY_LEFT)
		        		{
		        			if (trainer.facing_direction != 3)
		        			{
		        				trainer.face_west(); //1: north, 2: south, 3: west, 4:east
		        			}     
		        			else
		        			{
		        				trainer.move_west();
		        			}
		        			
		        		}

		        		if(key == FSKEY_RIGHT)
		        		{
		        			if (trainer.facing_direction != 4)
		        			{
		        				trainer.face_east(); //1: north, 2: south, 3: west, 4:east
		        			}     
		        			else
		        			{
		        				trainer.move_east();
		        			}
		        		}

		        		if(key == FSKEY_UP)
		        		{
		        			if (trainer.facing_direction != 1)
		        			{
		        				trainer.face_north(); //1: north, 2: south, 3: west, 4:east
		        			}     
		        			else
		        			{
		        				trainer.move_north();
		        			}
		        		}

		        		if (key == FSKEY_DOWN)
		        		{
		        			if (trainer.facing_direction != 2)
		        			{
		        				trainer.face_south(); //1: north, 2: south, 3: west, 4:east
		        			}     
		        			else
		        			{
		        				trainer.move_south();
		        			}
		        		}

						trainer.drawTrainer();

		        	}

		        	if (key == FSKEY_SPACE)
		        	{
		        		trainer.isMoving == false; //disable moving during the conversation

		        		People* people = identify_people_faced_by_trainer(trainer);

		        		trainer.conversation(people); //Inside the trainer class definition, there should be a while loop for the conversation

		        		if (people->name == "computer trainer")
		        		{
		        			scene_state = IN_BATTLE_SCENE;
		        		}
		        	}
		            
		            break;

		        case IN_BATTLE_SCENE:

		        	battle();

		        	//everything that happens in the battle scene
		            
		            break;

		        case IN_ANIMAL_POCKET:

		        	view_animal_pocket();

		        	//everything that happens in the animal pocket
		            
		            break;

		        case IN_MEDICINE_POCKET:

		        	view_medicine_pocket();

		        	//everything that happens in the medicine pocket
		            
		            break;

		        case TRANSIT_FROM_MAIN_TO_BATTLE:

		        	//there should be some animation here

		        	break;
		        }




		/*DYNAMIC MESSAGE TYPING*/
		/*Need to move this part to a member function of Trainer class*/

		if (message.typing_dynamic_message)
		{
			message.num_words_typed += 1;

    		if (message.num_words_typed > std::strlen(message.message_to_type))
    		{
    			message.typing_dynamic_message = false;
    			message.num_words_typed = 0;
    			
    			//chat_box.show_typed_message = true;
    			//player.Stop(type);

    		}
    		else
    		{
    			//void type_character(char* message_pointer, float start_x, float start_y, int start, int numChars);
    			message.type_character(message.message_to_type, 100,100, 0, message.num_words_typed);
    			//chat_box.move_cursor();

    		}
		}


		FsSwapBuffers();


		if (message.typing_dynamic_message)
		{
			FsSleep(100);
		}
		else
		{
			FsSleep(500);
		}
	}

	return 0;
}
