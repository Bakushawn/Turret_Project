#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// Constants
constexpr uint8_t PACKET_HEADER = 0xAA;

enum class TurretCommand : uint8_t {
    NONE = 0,
    AIM = 1,
    FIRE = 2
};

// enforcing tight 1-byte alignemnt for both compilers 
// pi is ARM64 and Arduino is 8-bit AVR
#pragma pack (push, 1)
struct TurretPacket{
    uint8_t header;
    TurretCommand command;
    uint8_t pan;
    uint8_t tilt;
    uint8_t checksum;
    
};
#pragma pack(pop)

#endif