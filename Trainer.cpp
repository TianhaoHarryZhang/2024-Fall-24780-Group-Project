#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include <string>
#include "Trainer.h"
#include "Utility.h"

const int Trainer::grid[22][38] = {
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Trainer::Trainer(const char* name, float x, float y) : People(name), x(x), y(y), facing_direction(2), moving(true), needHeal(false), inConversation(false)
{
	loadTrainer_png("images/trainer/trainer_front.png");
}

void Trainer::loadTrainer_png(const char* filePath)
{
	if (YSOK == Trainer_png.Decode(filePath))
	{
		Trainer_png.Flip();
	}
	else
	{
		printf("Failed to open file.\n");
	}
}

void Trainer::face_west()
{
	facing_direction = 3;
	loadTrainer_png("images/trainer/trainer_left.png");
}

void Trainer::face_east()
{
	facing_direction = 4;
	loadTrainer_png("images/trainer/trainer_right.png");
}

void Trainer::face_north()
{
	facing_direction = 1;
	loadTrainer_png("images/trainer/trainer_back.png");
}

void Trainer::face_south()
{
	facing_direction = 2;
	loadTrainer_png("images/trainer/trainer_front.png");
}

void Trainer::drawTrainer()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(static_cast<int>(x), static_cast<int>(y));
	glDrawPixels(Trainer_png.wid, Trainer_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Trainer_png.rgba);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

bool Trainer::isMoving()
{
	return moving;
}

void Trainer::move_west(int map_wid, int grid_size)
{
	if (!inConversation && x > 0)
	{
		int currentGridX = static_cast<int>(x / grid_size);
		int currentGridY = static_cast<int>(y / grid_size);

		float targetX = x - grid_size / 2;
		int targetGridX = static_cast<int>(targetX / grid_size);
		int targetGridY = currentGridY;

		if (targetGridX >= 0 && grid[targetGridY][targetGridX] == 1)
		{
			x = targetX;
			moving = true;
		}
	}
}

void Trainer::move_east(int map_wid, int grid_size)
{
	if (!inConversation && x + Trainer_png.wid < map_wid)
	{
		int currentGridX = static_cast<int>(x / grid_size);
		int currentGridY = static_cast<int>(y / grid_size);

		float targetX = x + grid_size / 2;
		int targetGridX = static_cast<int>(targetX / grid_size);
		int targetGridY = currentGridY;

		if (targetGridX < 38 && grid[targetGridY][targetGridX] == 1)
		{
			x = targetX;
			moving = true;
		}
	}
}

void Trainer::move_north(int map_hei, int grid_size)
{
	if (!inConversation && y - Trainer_png.hei > 0)
	{
		int currentGridX = static_cast<int>(x / grid_size);
		int currentGridY = static_cast<int>(y / grid_size);

		float targetY = y - grid_size / 2;
		int targetGridX = currentGridX;
		int targetGridY = static_cast<int>(targetY / grid_size);

		if (targetGridY >= 0 && grid[targetGridY][targetGridX] == 1)
		{
			y = targetY;
			moving = true;
		}
	}
}

void Trainer::move_south(int map_hei, int grid_size)
{
	if (!inConversation && y + Trainer_png.hei / 4 < map_hei)
	{
		int currentGridX = static_cast<int>(x / grid_size);
		int currentGridY = static_cast<int>(y / grid_size);

		float targetY = y + grid_size / 2;
		int targetGridX = currentGridX;
		int targetGridY = static_cast<int>(targetY / grid_size);

		if (targetGridY < 22 && grid[targetGridY][targetGridX] == 1)
		{
			y = targetY;
			moving = true;
		}
	}
}


bool Trainer::heal()
{
	//toggle healing action
	needHeal = !needHeal;
	//add code to increase health points to full
	return needHeal;
}

bool Trainer::isFacing(const People& person, int gridSize) const
{
	int trainerGridX = static_cast<int>(x / gridSize);
	int trainerGridY = static_cast<int>(y / gridSize);
	int personGridX = static_cast<int>(person.x / gridSize);
	int personGridY = static_cast<int>(person.y / gridSize);

	switch (facing_direction)
	{
	case 1:
		return trainerGridX == personGridX && trainerGridY - 1 == personGridY;	//facing north
	case 2:
		return trainerGridX == personGridX && trainerGridY + 2 == personGridY;	//facing south
	case 3:
		return ((trainerGridY == personGridY || trainerGridY + 1 == personGridY) && trainerGridX - 1 == personGridX);	//facing west
	case 4:
		return ((trainerGridY == personGridY || trainerGridY + 1 == personGridY) && trainerGridX + 1 == personGridX);	//facing east
	default:
		return false;
	}
}

void Trainer::interactWith(People& otherCharacter, YsRawPngDecoder& main_scene, People& nurse, People& comp)
{
	inConversation = true;
	moving = false;

	int screenWidth = main_scene.wid;
	int screenHeight = main_scene.hei;

	for (int i = 0; i < 10; ++i)
	{
		const char* message = otherCharacter.getMessage(i);
		if (message == nullptr) break;

		for (int j = 1; j <= strlen(message); ++j)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glDisable(GL_BLEND);
			glRasterPos2i(0, screenHeight - 1);
			glDrawPixels(main_scene.wid, main_scene.hei, GL_RGBA, GL_UNSIGNED_BYTE, main_scene.rgba);
			drawTrainer();
			nurse.drawPeople();
			comp.drawPeople();

			glColor3ub(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex2i(5, screenHeight - 105);
			glVertex2i(screenWidth - 5, screenHeight - 105);
			glVertex2i(screenWidth - 5, screenHeight - 5);
			glVertex2i(5, screenHeight - 5);
			glEnd();

			glColor3ub(255, 255, 255);
			glBegin(GL_QUADS);
			glVertex2i(10, screenHeight - 100);
			glVertex2i(screenWidth - 10, screenHeight - 100);
			glVertex2i(screenWidth - 10, screenHeight - 10);
			glVertex2i(10, screenHeight - 10);
			glEnd();

			Message msg;
			msg.type_character(const_cast<char*>(message), 20, screenHeight - 50, 0, j);

			FsSwapBuffers();
			FsSleep(50);
		}
		FsSleep(1000);
	}
	inConversation = false;
	moving = true;
}


//void Trainer::displayPokemon(Trainer* trainer, Scene_State* scene_state, void* pokemon_scene, YsSoundPlayer* player, YsSoundPlayer::SoundData* sound)
//{
//	YsRawPngDecoder* png = (YsRawPngDecoder*)pokemon_scene;
//	// make an array of medicine images
//	YsRawPngDecoder animal1, animal2;
//	if (YSOK != animal1.Decode("images/monster/dog.png") || YSOK != animal2.Decode("images/monster/rabbit.png"))
//	{
//		printf("Failed to open file.\n");
//		return;
//	}
//
//	// Flip the images once after decoding if needed
//	animal1.Flip();
//	animal2.Flip();
//
//	for (;;)
//	{
//		FsPollDevice();
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		auto key = FsInkey();
//
//		if (FSKEY_ESC == key)
//		{
//			exit(0);
//		}
//
//		int mouseEvent;
//		int lb, mb, rb, mx, my;
//		int cure = 0;
//		mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
//		if (FSMOUSEEVENT_LBUTTONDOWN == mouseEvent)
//		{
//			printf("Mouse down at %d %d\n", mx, my);
//			if (mx > 300 && mx < 550 && my > 161 && my < 521)
//			{
//				// TODO: get the pokemon's name and the HP
//				printf("Animal1 clicked\n");
//
//				// play sound
//				player->PlayOneShot(*sound);
//				trainer->currentPokemonIndex = 0;
//			}
//			else if (mx > 700 && mx < 950 && my > 161 && my < 521)
//			{
//				// TODO: get the pokemon's name and the HP
//				printf("Animal2 clicked\n");
//				// play sound
//				player->PlayOneShot(*sound);
//				trainer->currentPokemonIndex = 1;
//			}
//			*scene_state = IN_BATTLE_SCENE;
//			break;
//		}
//
//		glColor3ub(0, 0, 0);
//		// glRasterPos2d(380, 445);
//		//  TODO: get pokemon's HP
//		//  YsGlDrawFontBitmap16x20("60");
//		int HP1 = pokemon[0].getHP();
//		YsRawPngDecoder number1;
//
//		generate_number_png(HP1, 30, 30, 20, 214, 202, 172, "number1");
//		if (YSOK != number1.Decode("number1.png"))
//		{
//			printf("Failed to open number1.\n");
//			return;
//		}
//		number1.Flip();
//		glPixelZoom(1, 1);
//		glRasterPos2i(380, 445);
//		glDrawPixels(number1.wid, number1.hei, GL_RGBA, GL_UNSIGNED_BYTE, number1.rgba);
//		// width range  300 < x < 550 (width of the image is 623, ratio 0.4; 627 * 0.4 = 250)
//		// height range 520 < y < 1413 (height of the image is 898, ratio 0.4; 893 * 0.4 = 359)
//		glRasterPos2i(300, 520); // Example position for animal1
//		glPixelZoom(0.4, 0.4);
//		glDrawPixels(animal1.wid, animal1.hei, GL_RGBA, GL_UNSIGNED_BYTE, animal1.rgba);
//
//		glColor3ub(0, 0, 0);
//		// glRasterPos2d(780, 445);
//		//  TODO: get pokemon's HP
//		//  YsGlDrawFontBitmap16x20("80");
//		//  printf("Potion1 Width: %d Height: %d\n", animal1.wid, animal1.hei);
//		int HP2 = pokemon[1].getHP();
//		YsRawPngDecoder number2;
//
//		generate_number_png(HP2, 30, 30, 20, 214, 202, 172, "number2");
//
//		if (YSOK != number2.Decode("number2.png"))
//		{
//			printf("Failed to open number2.\n");
//			return;
//		}
//		number2.Flip();
//		glPixelZoom(1, 1);
//		glRasterPos2d(780, 445);
//		glDrawPixels(number2.wid, number2.hei, GL_RGBA, GL_UNSIGNED_BYTE, number2.rgba);
//		// width range 700 < x < 950 (width of the image is 627, ratio 0.4; 627 * 0.4 = 250)
//		// height range 520 < y < 1415 (height of the image is 898, ratio 0.4; 898 * 0.4 = 359)
//		glRasterPos2i(700, 520); // Example position for potion2
//		glPixelZoom(0.4, 0.4);
//		glDrawPixels(animal2.wid, animal2.hei, GL_RGBA, GL_UNSIGNED_BYTE, animal2.rgba);
//
//		// printf("Potion2 Width: %d Height: %d\n", animal2.wid, animal2.hei);
//
//		glPixelZoom(1, 1);
//		glRasterPos2i(0, png->hei - 1);
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glDrawPixels(png->wid, png->hei, GL_RGBA, GL_UNSIGNED_BYTE, png->rgba);
//
//		FsSwapBuffers();
//		FsSleep(10);
//	}
//}