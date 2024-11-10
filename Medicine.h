#include <iostream>
#include <string>

const int MAX_MEDICINE = 3;

class Medicine
{

private:
    std::string name;
    int cure;

public:
    Medicine(std::string name, int cure);

    std::string getName();

    int getCure();

    void useMedicine();

    void displayMedicine();
};

class MedicinePocket
{
private:
    // list of medicines
    Medicine *medicines;
    // size of the list
    int size;
    // list of medicine names
    std::string medicineNames[MAX_MEDICINE] = {"Healixir", "Serene Sap", "Restoraid"};
    // list of cure values
    int cureValues[MAX_MEDICINE] = {10, 20, 40};

public:
    MedicinePocket();

    ~MedicinePocket();

    void useMedicine(int index);

    void displayMedicines();
};