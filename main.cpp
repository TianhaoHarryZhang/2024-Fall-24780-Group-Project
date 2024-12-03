#include <cstring>
#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "utility.h"
#include "Trainer.h"
//#include "Medicine.h"
//#include "BattleScene.h"
#include "Scene.h"

void Render(void *incoming)
{
	YsRawPngDecoder *pngPtr = (YsRawPngDecoder *)incoming;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	int winWid, winHei;
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(0.0, (double)(winHei - 1));
	glDrawPixels(pngPtr->wid, pngPtr->hei, GL_RGBA, GL_UNSIGNED_BYTE, pngPtr->rgba);

	FsSwapBuffers();
}

int main(void)
{
	FsChangeToProgramDir();

	YsRawPngDecoder main_scene, blur_scene;

	Message message;

	//Trainer trainer("Ash", 68, 102);
	Trainer trainer("Ash", 442, 238);
	People nurse("Nurse", 480, 255);
	People comp("Comp", 755, 629);
	
	nurse.loadPeople("images/trainer/nurse.png");
	comp.loadPeople("images/trainer/computer.png");

	//MedicinePocket medicine_pocket;

	//PokemonUI UI;

	//YsSoundPlayer player;
	//player.MakeCurrent();
	//player.Start();
	//FsChangeToProgramDir();

	//YsSoundPlayer::SoundData bkground, notification;
	//load_sound(bkground, "audio/Background.wav");
	//load_sound(notification, "audio/Notification_1.wav");

	//player.PlayBackground(bkground);

	Scene_State scene_state = IN_LOAD_SCENE;
	scene_state = IN_MAIN_SCENE;

	if (YSOK == main_scene.Decode("images/new_version.png"))
	{
		printf("Wid %d Hei %d\n", main_scene.wid, main_scene.hei);
		main_scene.Flip();
	}
	else
	{
		printf("Failed to open file.\n");
		return 1;
	}

	if (YSOK == blur_scene.Decode("images/blur_background.png"))
	{
		printf("Wid %d Hei %d\n", blur_scene.wid, blur_scene.hei);
		blur_scene.Flip();
	}
	else
	{
		printf("Failed to open file.\n");
		return 1;
	}

	FsOpenWindow(0, 0, main_scene.wid, main_scene.hei, 1);

	for (;;)
	{
		FsPollDevice();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto key = FsInkey();

		if (FSKEY_ESC == key)
		{
			break;
		}

		switch (scene_state)
		{

		//case IN_LOAD_SCENE:

		//	game_loading(&scene_state);

		case IN_MAIN_SCENE:
			//  draw the background image
			glRasterPos2i(0, main_scene.hei - 1);
			glDrawPixels(main_scene.wid, main_scene.hei, GL_RGBA, GL_UNSIGNED_BYTE, main_scene.rgba);
			int w = main_scene.wid;
			int h = main_scene.hei;
			int grid_size = 34;

			nurse.addMessage("Welcome to the Pokemon Center!");
			nurse.addMessage("Would you like to heal your Pokemon?");
			nurse.addMessage("Take care!");

			comp.addMessage("I am a computer.");
			comp.addMessage("Accessing Pokemon storage system.");

			// move the trainer
			if (trainer.moving == true)
			{
				if (key == FSKEY_LEFT)
				{
					if (trainer.facing_direction != 3)
					{
						trainer.face_west(); // 1: north, 2: south, 3: west, 4:east
					}
					else
					{
						trainer.move_west(w, grid_size);
					}
				}

				if (key == FSKEY_RIGHT)
				{
					if (trainer.facing_direction != 4)
					{
						trainer.face_east(); // 1: north, 2: south, 3: west, 4:east
					}
					else
					{
						trainer.move_east(w, grid_size);
					}
				}

				if (key == FSKEY_UP)
				{
					if (trainer.facing_direction != 1)
					{
						trainer.face_north(); // 1: north, 2: south, 3: west, 4:east
					}
					else
					{
						trainer.move_north(h, grid_size);
					}
				}

				if (key == FSKEY_DOWN)
				{
					if (trainer.facing_direction != 2)
					{
						trainer.face_south(); // 1: north, 2: south, 3: west, 4:east
					}
					else
					{
						trainer.move_south(h, grid_size);
					}
				}
				trainer.drawTrainer();
			}

			if (key == FSKEY_SPACE)
			{
				if (trainer.isFacing(nurse, grid_size))
				{
					trainer.interactWith(nurse);
				}
				else if (trainer.isFacing(comp, grid_size))
				{
					trainer.interactWith(comp);
				}
			}

			// 	if (people->name == "computer trainer")
			// 	{
			// 		scene_state = IN_BATTLE_SCENE;
			// 	}
			// }

			nurse.drawPeople();
			comp.drawPeople();

			break;

		//case IN_BATTLE_SCENE:

		//	UI.battle(&scene_state, &player, &notification);

		//	// everything that happens in the battle scene

		//	break;

		//case IN_ANIMAL_POCKET:

		//	trainer.displayPokemon(&scene_state, &blur_scene, &player, &notification);

		//	// everything that happens in the animal pocket

		//	break;

		//case IN_MEDICINE_POCKET:

		//	medicine_pocket.displayMedicines(&scene_state, &blur_scene, &player, &notification);

		//	break;
		//case TRANSIT_FROM_MAIN_TO_BATTLE:

		//	// there should be some animation here

		//	break;
		}

		/*DYNAMIC MESSAGE TYPING*/
		/*Need to move this part to a member function of Trainer class*/

		//if (message.typing_dynamic_message)
		//{
		//	message.num_words_typed += 1;

		//	if (message.num_words_typed > std::strlen(message.message_to_type))
		//	{
		//		message.typing_dynamic_message = false;
		//		message.num_words_typed = 0;

		//		// chat_box.show_typed_message = true;
		//		// player.Stop(type);
		//	}
		//	else
		//	{
		//		// void type_character(char* message_pointer, float start_x, float start_y, int start, int numChars);
		//		message.type_character(message.message_to_type, 100, 100, 0, message.num_words_typed);
		//		// chat_box.move_cursor();
		//	}
		//}

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
