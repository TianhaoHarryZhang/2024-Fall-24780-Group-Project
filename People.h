#include <stdio.h>

class People
{
private:

	char conversationMessages[10][100];
	int messageCount;
	float x, y;

public:
	
	char name[50];
	People(const char* characterName, float x = 0.0, float y = 0.0);
	const char* getName() const;
	void addMessage(const char* message);

};
