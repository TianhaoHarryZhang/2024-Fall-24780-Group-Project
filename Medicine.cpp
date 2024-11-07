#include <iostream>
#include <string>
#include "Medicine.h"

Medicine::Medicine(std::string name = NULL, int cure = 0) : name(name), cure(cure) {}

std::string Medicine::getName() const
{
    return name;
}

int Medicine::getCure() const
{
    return cure;
}

void Medicine::useMedicine()
{
    cure = 0;
}

void Medicine::displayMedicine()
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Cure: " << cure << std::endl;
}

// MedicinePocket
MedicinePocket::MedicinePocket() : size(0)
{
    medicines = new Medicine[MAX_MEDICINE];
    for (int i = 0; i < MAX_MEDICINE; i++)
    {
        medicines[i] = Medicine(medicineNames[i], cureValues[i]);
        size++;
    }
}

MedicinePocket::~MedicinePocket()
{
    delete[] medicines;
}

void MedicinePocket::useMedicine(int index)
{
    if (index >= 0 && index < size)
    {
        medicines[index].useMedicine();
    }
}

void MedicinePocket::displayMedicines()
{
    for (int i = 0; i < size; i++)
    {
        medicines[i].displayMedicine();
    }
}
