#include <stdio.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"
#include "Trainer.h" 

Trainer::Trainer(const char* name, float x, float y) : People(name), x(x), y(y), facing_direction(2), needHeal(false)
{
	loadTrainer_png("images/trainer/trainer_front.png");
}

void Trainer::loadTrainer_png(const char* filePath)
{
	if (YSOK == Trainer_png.Decode(filePath))
	{
		printf("Wid %d Hei %d\n", Trainer_png.wid, Trainer_png.hei);
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
	glRasterPos2i(static_cast<int>(x), static_cast<int>(y));
	glDrawPixels(Trainer_png.wid, Trainer_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, Trainer_png.rgba);
}

bool Trainer::isMoving()
{
	return moving;
}

void Trainer::move_west()
{
	if (!inConversation)
	{
		x -= 10;
		moving = true;
		//once dimensions are established, add code to prevent trainer from exiting map boundaries
	}
}

void Trainer::move_east()
{
	if (!inConversation)
	{
		x += 10;
		moving = true;
		//once dimensions are established, add code to prevent trainer from exiting map boundaries
	}
}

void Trainer::move_north()
{
	if (!inConversation)
	{
		y += 10;
		moving = true;
		//once dimensions are established, add code to prevent trainer from exiting map boundaries
	}
}

void Trainer::move_south()
{
	if (!inConversation)
	{
		y -= 10;
		moving = true;
		//once dimensions are established, add code to prevent trainer from exiting map boundaries
	}
}

bool Trainer::heal()
{
	//toggle healing action
	needHeal = !needHeal;
	//add code to increase health points to full
	return needHeal;
}

void Trainer::interactWith(People& otherCharacter)
{
	//add code to initiate conversation

	//add code for conversation
	inConversation = true;
	moving = false;

	inConversation = false;
}
