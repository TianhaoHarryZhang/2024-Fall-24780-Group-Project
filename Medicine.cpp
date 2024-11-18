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

void Medicine::displayMedicine(int i)
{
    // display the name and cure value of the medicine
    YsRawPngDecoder png;
    std::string filename = "images/medicine/potion" + std::to_string(i + 1) + ".png";
    if (YSOK != png.Decode(filename.c_str()))
    {
        printf("Failed to open file.\n");
        return;
    }

    glRasterPos2i(png.wid + 10, png.hei - 1);
    glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
    // std::cout << "Name: " << name << std::endl;
    // std::cout << "Cure: " << cure << std::endl;

    // printf("Name: %s Width: %d Height: %d\n", name.c_str(), potion1.wid, potion2.hei);
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

void MedicinePocket::displayMedicines(void *medicine_scene)
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
            break;
        }

        // display the medicine image on the screen
        glRasterPos2i(140, 520); // Example position for potion1
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion1.wid, potion1.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion1.rgba);

        glRasterPos2i(490, 520); // Example position for potion2
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion2.wid, potion2.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion2.rgba);

        glRasterPos2i(840, 520); // Example position for potion3
        glPixelZoom(0.4, 0.4);
        glDrawPixels(potion3.wid, potion3.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion3.rgba);

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
