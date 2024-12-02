#include <stdio.h>

class People
{
private:
    char name[50];
    char conversationMessages[10][100];
    int messageCount;
    float x, y;

public:
    People(const char *characterName, float x = 0.0, float y = 0.0);
    const char *getName() const;
    void addMessage(const char *message);
};