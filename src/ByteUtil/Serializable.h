#pragma once

#include <vector>

class Serializable
{
public:
	void AppendBytes(std::vector<char>& buffer);
	std::vector<char> GetBytes();
protected:
	virtual void _getBytes(std::vector<char>& buffer) = 0;
};