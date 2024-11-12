#include <stdio.h>
#include "People.h"
#include <string.h>

People::People(const char* characterName, float x = 0.0, float y = 0.0) : x(x), y(y), messageCount(0)
{
	strncpy(name, characterName, sizeof(name) - 1);
	name[sizeof(name) - 1] = "\0"
}

const char* People::getName() const {
    return name;
}

void People::addMessage(const char* message) {
    //insert code to process conversation messages
}
