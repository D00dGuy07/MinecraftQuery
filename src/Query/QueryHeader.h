#pragma once

#include <cstdint>
#include <vector>

#include "../ByteUtil/Serializable.h"

#define QUERY_TYPE_HANDSHAKE 9
#define QUERY_TYPE_STAT 0

struct QueryHeader : public Serializable
{
    unsigned short Magic = 0xFEFD;
    uint8_t Type;
    int32_t ID;

    QueryHeader(uint8_t type, int32_t id) : Type(type), ID(id) {}

protected:
    virtual void _getBytes(std::vector<char>& buffer) override;
};