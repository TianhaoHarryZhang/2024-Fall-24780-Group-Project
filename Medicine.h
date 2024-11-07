#include <iostream>
#include <string>

const int MAX_MEDICINE = 2;

class Medicine
{

private:
    std::string name;
    int cure;

public:
    Medicine(std::string name, int cure);

    std::string getName() const;

    int getCure() const;

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
    std::string medicineNames[MAX_MEDICINE] = {"Potion", "Super Potion"};
    // list of cure values
    int cureValues[MAX_MEDICINE] = {20, 50};

public:
    MedicinePocket();

    ~MedicinePocket();

    void useMedicine(int index);

    void displayMedicines();
};