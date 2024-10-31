#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"


int main(void)
{
	FsChangeToProgramDir();

	YsRawPngDecoder main_scene;

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

		if(FSKEY_ESC==FsInkey())
		{
			break;
		}


		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,main_scene.hei-1);
		glDrawPixels(main_scene.wid, main_scene.hei, GL_RGBA, GL_UNSIGNED_BYTE, main_scene.rgba);

		FsSwapBuffers();
	}

	return 0;
}
