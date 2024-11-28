#include <stdio.h>
#include "People.h"
#include <string.h>

People::People(const char* characterName, float x, float y)
    : x(x), y(y), messageCount(0)
{
    strncpy(name, characterName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

const char* People::getName() const {
    return name;
}

void People::addMessage(const char* message) {
    if (messageCount < 10) {
        strncpy(conversationMessages[messageCount], message, sizeof(conversationMessages[messageCount]) - 1);
        conversationMessages[messageCount][sizeof(conversationMessages[messageCount]) - 1] = '\0';
        ++messageCount;
    }
    else {
        printf("Exceeds message limit\n");
    }
}