#include <stdio.h>
#include "yspng.h"
#include "yspngenc.h"

class People
{
private:

    char conversationMessages[10][100];
    int messageCount;
    YsRawPngDecoder People_png;

public:

    float x, y;
    People(const char* characterName, float x = 0.0, float y = 0.0);
    void loadPeople(const char* filePath);
    void drawPeople();

    char name[50];
    const char* getName() const;
    const char* getMessage(int index) const;
    void addMessage(const char* message);
};