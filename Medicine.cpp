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

void Medicine::displayMedicine()
{
    // display the name and cure value of the medicine
    YsRawPngDecoder potion1, potion2, potion3;
    if (YSOK != potion1.Decode("images/medicine/potion1.png") or YSOK != potion2.Decode("images/medicine/potion2.png") or YSOK != potion3.Decode("images/medicine/potion3.png"))
    {
        printf("Failed to open file.\n");
        return;
    }

    // glRasterPos2i(potion1.wid + 10, potion2.hei - 1);
    // glDrawPixels(potion2.wid, potion2.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion2.rgba);
    std::cout << "Name: " << name << std::endl;
    std::cout << "Cure: " << cure << std::endl;
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
}

void MedicinePocket::displayMedicines(void *medicine_scene)
{
    YsRawPngDecoder *png = (YsRawPngDecoder *)medicine_scene;
    glRasterPos2i(0, png->hei - 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawPixels(png->wid, png->hei, GL_RGBA, GL_UNSIGNED_BYTE, png->rgba);

    YsRawPngDecoder potion1, potion2, potion3;
    if (YSOK != potion1.Decode("images/medicine/potion1.png") or YSOK != potion2.Decode("images/medicine/potion2.png") or YSOK != potion3.Decode("images/medicine/potion3.png"))
    {
        printf("Failed to open file.\n");
        return;
    }

    glRasterPos2i(0, potion1.hei - 1);
    glDrawPixels(potion1.wid, potion1.hei, GL_RGBA, GL_UNSIGNED_BYTE, potion1.rgba);
    // for (int i = 0; i < size; i++)
    // {
    //     medicines[i].displayMedicine();
    // }
}
