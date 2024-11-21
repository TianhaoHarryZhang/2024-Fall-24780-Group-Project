#include <stdio.h>
#include "People.h"
#include <string.h>

People::People(const char *characterName, float x, float y) : x(x), y(y), messageCount(0)
{
    strncpy(name, characterName, sizeof(name) - 1);
}

const char *People::getName() const
{
    return name;
}

void People::addMessage(const char *message)
{
    // insert code to process conversation messages
}