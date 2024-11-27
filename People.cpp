#include <stdio.h>
#include "People.h"
#include <string.h>

People::People(const char* characterName, float x, float y)
    : x(x), y(y), messageCount(0) // Default arguments removed here
{
    // Safely copy characterName into the name array
    strncpy(name, characterName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0'; // Null-terminate
}

const char* People::getName() const {
    return name;
}

void People::addMessage(const char* message) {
    // Insert code to process conversation messages
}