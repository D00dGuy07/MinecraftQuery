#include "QueryHeader.h"

#include "../ByteUtil/Bytes.h"

void QueryHeader::_getBytes(std::vector<char>& buffer)
{
	SerializeBytes(buffer, Magic);
	buffer.emplace_back(Type);
	SerializeBytes(buffer, ID);
}
