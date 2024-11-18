#include <stdio.h>
#include "Trainer.h"

Trainer::Trainer(const char *name, float x, float y) : People(name), x(x), y(y), needHeal(false) {}

void Trainer::move(float dx, float dy)
{
	x += dx;
	y += dy;
	// once dimensions are established, add code to prevent trainer from exiting map boundaries
}

bool Trainer::heal()
{
	// toggle healing action
	needHeal = !needHeal;
	// add code to increase health points to full
}

void Trainer::interactWith(People &otherCharacter)
{
	// add code to initiate conversation

	// add code for conversation
}

void Trainer::displayPokemon(void *pokemon_scene)
{
	YsRawPngDecoder *png = (YsRawPngDecoder *)pokemon_scene;
	// make an array of medicine images
	YsRawPngDecoder animal1, animal2;
	if (YSOK != animal1.Decode("images/monster/dog.png") or YSOK != animal2.Decode("images/monster/rabbit.png"))
	{
		printf("Failed to open file.\n");
		return;
	}

	// Flip the images once after decoding if needed
	animal1.Flip();
	animal2.Flip();

	for (;;)
	{
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto key = FsInkey();

		if (FSKEY_ESC == key)
		{
			break;
		}

		int mouseEvent;
		int lb, mb, rb, mx, my;
		int cure = 0;
		mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
		if (FSMOUSEEVENT_LBUTTONDOWN == mouseEvent)
		{
			printf("Mouse down at %d %d\n", mx, my);
			if (mx > 300 && mx < 550 && my > 161 && my < 521)
			{
				// TODO: get the pokemon's name and the HP
				printf("Animal1 clicked\n");
			}
			else if (mx > 700 && mx < 950 && my > 161 && my < 521)
			{
				// TODO: get the pokemon's name and the HP
				printf("Animal2 clicked\n");
			}
		}

		glColor3ub(0, 0, 0);
		glRasterPos2d(380, 445);
		// TODO: get pokemon's HP
		YsGlDrawFontBitmap16x20("60");
		// width range  300 < x < 550 (width of the image is 623, ratio 0.4; 627 * 0.4 = 250)
		// height range 520 < y < 1413 (height of the image is 898, ratio 0.4; 893 * 0.4 = 359)
		glRasterPos2i(300, 520); // Example position for animal1
		glPixelZoom(0.4, 0.4);
		glDrawPixels(animal1.wid, animal1.hei, GL_RGBA, GL_UNSIGNED_BYTE, animal1.rgba);

		glColor3ub(0, 0, 0);
		glRasterPos2d(780, 445);
		// TODO: get pokemon's HP
		YsGlDrawFontBitmap16x20("80");
		// printf("Potion1 Width: %d Height: %d\n", animal1.wid, animal1.hei);

		// width range 700 < x < 950 (width of the image is 627, ratio 0.4; 627 * 0.4 = 250)
		// height range 520 < y < 1415 (height of the image is 898, ratio 0.4; 898 * 0.4 = 359)
		glRasterPos2i(700, 520); // Example position for potion2
		glPixelZoom(0.4, 0.4);
		glDrawPixels(animal2.wid, animal2.hei, GL_RGBA, GL_UNSIGNED_BYTE, animal2.rgba);

		// printf("Potion2 Width: %d Height: %d\n", animal2.wid, animal2.hei);

		glPixelZoom(1, 1);
		glRasterPos2i(0, png->hei - 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawPixels(png->wid, png->hei, GL_RGBA, GL_UNSIGNED_BYTE, png->rgba);

		FsSwapBuffers();
		FsSleep(10);
	}
}