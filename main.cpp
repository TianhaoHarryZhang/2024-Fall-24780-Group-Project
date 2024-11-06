#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"


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


		if(FSKEY_ESC==FsInkey())
		{
			break;
		}


		switch (scene_state) {

		        case IN_MAIN_SCENE:
		            
		        	//everything that happens in the main scene
		        	glRasterPos2i(0,main_scene.hei-1);
					glDrawPixels(main_scene.wid, main_scene.hei, GL_RGBA, GL_UNSIGNED_BYTE, main_scene.rgba);

		            break;

		        case IN_BATTLE_SCENE:

		        	//everything that happens in the battle scene
		            
		            break;

		        case IN_ANIMAL_POCKET:

		        	//everything that happens in the animal pocket
		            
		            break;

		        case IN_MEDICINE_POCKET:

		        	//everything that happens in the medicine pocket
		            
		            break;

		        case TRANSIT_FROM_MAIN_TO_BATTLE:

		        	//there should be some animation here

		        	break;
		        }


		FsSwapBuffers();
	}

	return 0;
}
