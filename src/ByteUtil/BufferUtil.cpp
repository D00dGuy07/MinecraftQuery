#include <string>

std::string ReadString(char*& pointer)
{
	std::string string(pointer);

	// Advance pointer to beyond the string
	char currentCharacter = *pointer;
	while (currentCharacter != NULL)
	{
		pointer++;
		currentCharacter = *pointer;
	}
	pointer++;

	return string;
}