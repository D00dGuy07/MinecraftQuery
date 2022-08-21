#pragma once

#include <vector>

void SerializeBytes(std::vector<char>& buffer, int data);
void SerializeBytes(std::vector<char>& buffer, short data);
void SerializeBytes(std::vector<char>& buffer, unsigned short data);