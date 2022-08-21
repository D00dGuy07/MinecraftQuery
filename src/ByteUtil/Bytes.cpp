#include <vector>

void SerializeBytes(std::vector<char>& buffer, int data)
{
    buffer.emplace_back(data >> 24);
    buffer.emplace_back((data >> 16) & 0x000000FF);
    buffer.emplace_back((data >> 8) & 0x000000FF);
    buffer.emplace_back(data & 0x000000FF);
}

void SerializeBytes(std::vector<char>& buffer, short data)
{
    buffer.emplace_back(data >> 8);
    buffer.emplace_back(data & 0x00FF);
}

void SerializeBytes(std::vector<char>& buffer, unsigned short data)
{
    buffer.emplace_back(data >> 8);
    buffer.emplace_back(data & 0x00FF);
}