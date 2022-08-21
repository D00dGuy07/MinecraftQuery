#include "Serializable.h"

void Serializable::AppendBytes(std::vector<char>& buffer)
{
	_getBytes(buffer);
}

std::vector<char> Serializable::GetBytes()
{
	std::vector<char> buffer = std::vector<char>();
	_getBytes(buffer);
	return buffer;
}