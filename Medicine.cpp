#include "Medicine.h"

std::string Medicine::getName()
{
    return name;
}

int Medicine::getCure()
{
    return cure;
}

void Medicine::useMedicine()
{
    cure = 0;
}

// MedicinePocket
MedicinePocket::MedicinePocket() : size(MAX_MEDICINE)
{
    for (int i = 0; i < size; i++)
    {
        medicines[i].name = medicineNames[i];
        medicines[i].cure = cureValues[i];
    }
}

int MedicinePocket::useMedicine(int index)
{
    if (index >= 0 && index < size)
    {
        int cure = medicines[index].getCure();
        return cure;
    }
    return 0;
}

void MedicinePocket::displayMedicines(void *medicine_scene, YsSoundPlayer *player, YsSoundPlayer::SoundData *sound)
{

    YsRawPngDecoder *png = (YsRawPngDecoder *)medicine_scene;
    // make an array of medicine images
    YsRawPngDecoder potion1, potion2, potion3;
    if (YSOK != potion1.Decode("images/medicine/potion1.png") or YSOK != potion2.Decode("images/medicine/potion2.png") or YSOK != potion3.Decode("images/medicine/potion3.png"))
    {
        printf("Failed to open file.\n");
        return;
    }

    // Flip the images once after decoding if needed
    potion1.Flip();
    potion2.Flip();
    potion3.Flip();

    for (;;)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto key = FsInkey();

        if (FSKEY_ESC == key)
        {
            exit(0);
        }

        int mouseEvent;
        int lb, mb, rb, mx, my;
        int cure = 0;
        mouseEvent = FsGetMouseEvent(lb, mb, rb, mx, my);
        if (FSMOUSEEVENT_LBUTTONDOWN == mouseEvent)
        {
            printf("Mouse down at %d %d\n", mx, my);
            if (140 < mx && mx < 391 && 162 < my && my < 521)
            {
                cure = useMedicine(0);
                // play sound
                player->PlayOneShot(*sound);
            }
            else if (490 < mx && mx < 741 && 162 < my && my < 521)
            {
                cure = useMedicine(1);
                // play sound
                player->PlayOneShot(*sound);
            }
            else if (840 < mx && mx < 1090 && 162 < my && my < 521)
            {
                cure = useMedicine(2);
                // play sound
                player->PlayOneShot(*sound);
            }
            printf("Cure: %d\n", cure);
        }
        // display the medicine image on the screen
        // width range 140 < x < 767 (width of the image is 627, ratio 0.4; 627 * 0.4 = 250)
        // height range 520 < y < 1413 (height of the image is 893, ratio 0.4; 893 * 0.4 = 357)
        glRasterPos2i(140, 520); // Example position for potion1
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion1.wid, potion1.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion1.rgba);
        // printf("Potion1 Width: %d Height: %d\n", potion1.wid, potion1.hei);

        // width range 490 < x < 1117 (width of the image is 627, ratio 0.4; 627 * 0.4 = 250)
        // height range 520 < y < 1413 (height of the image is 893, ratio 0.4; 893 * 0.4 = 357)
        glRasterPos2i(490, 520); // Example position for potion2
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion2.wid, potion2.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion2.rgba);
        // printf("Potion2 Width: %d Height: %d\n", potion2.wid, potion2.hei);

        // width range 840 < x < 1463 (width of the image is 623, ratio 0.4; 623 * 0.4 = 249)
        // height range 520 < y < 1413 (height of the image is 893, ratio 0.4; 893 * 0.4 = 357)
        glRasterPos2i(840, 520); // Example position for potion3
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion3.wid, potion3.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion3.rgba);
        // printf("Potion3 Width: %d Height: %d\n", potion3.wid, potion3.hei);

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
