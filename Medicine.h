#include <iostream>
#include <string>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yssimplesound.h"
#include "ysglfontdata.h"
#include "yspngenc.h"

const int MAX_MEDICINE = 3;

class Medicine
{
public:
    std::string name;
    int cure;

    std::string getName();

    int getCure();

    void useMedicine();

    void displayMedicine();
};

class MedicinePocket
{
private:
    // list of medicines
    Medicine medicines[MAX_MEDICINE];
    // size of the list
    int size;
    // list of medicine names
    std::string medicineNames[MAX_MEDICINE] = {"Medicine1", "Medicine2", "Medicine3"};
    // list of cure values
    int cureValues[MAX_MEDICINE] = {10, 20, 40};

public:
    MedicinePocket();

    int useMedicine(int index);

    void displayMedicines(void *medicine_scene);
};