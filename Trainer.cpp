#include <stdio.h>
#include "Trainer.h" 

Trainer::Trainer(const char* name, float x, float y) : People(name), x(x), y(y), needHeal(false) {}

void Trainer::move(float dx, float dy)
{
	x += dx;
	y += dy;
	//once dimensions are established, add code to prevent trainer from exiting map boundaries
}

bool Trainer::heal()
{
	//toggle healing action
	needHeal = !needHeal;
	//add code to increase health points to full
}

void Trainer::interactWith(People& otherCharacter)
{
	//add code to initiate conversation

	//add code for conversation
}
