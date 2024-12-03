#include <stdio.h>
#include "People.h"
#include <string.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"

People::People(const char* characterName, float x, float y)
    : x(x), y(y), messageCount(0)
{
    strncpy(name, characterName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

void People::loadPeople(const char* filePath)
{
    if (YSOK == People_png.Decode(filePath))
    {
        People_png.Flip();
    }
    else
    {
        printf("Failed to open file.\n");
    }
}

void People::drawPeople()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRasterPos2i(static_cast<int>(x), static_cast<int>(y));
    glDrawPixels(People_png.wid, People_png.hei, GL_RGBA, GL_UNSIGNED_BYTE, People_png.rgba);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

const char* People::getName() const {
    return name;
}

const char* People::getMessage(int index) const
{
    if (index >= 0 && index < messageCount)
    {
        return conversationMessages[index];
    }
    return nullptr;
}


void People::addMessage(const char* message) {
    if (messageCount < 10)
    {
        strncpy(conversationMessages[messageCount], message, sizeof(conversationMessages[messageCount]) - 1);
        conversationMessages[messageCount][sizeof(conversationMessages[messageCount]) - 1] = '\0';
        ++messageCount;
    }
}

void People::initializeMessages()
{
    if (!messagesInitialized)
    {
        if (strcmp(name, "Nurse Joy") == 0)
        {
            addMessage("Welcome to the Pokemon Center!");
            addMessage("Would you like to heal your Pokemon?");
            addMessage("Take care!");
        }
        else if (strcmp(name, "Gary") == 0)
        {
            addMessage("I am a computer.");
            addMessage("Accessing Pokemon storage system.");
        }
        messagesInitialized = true;
    }
}
