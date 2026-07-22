#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <cstdint>
#include <algorithm>

#include "..\shared\Protocol.h"

struct CommandData {
    bool valid;
    int pan;
    int tilt;
    bool fire;
};

class CommandParser {
public:
    static uint8_t calculateChecksum(const TurretPacket& packet){
        return packet.header ^ static_cast<uint8_t>(packet.command) ^ packet.pan ^ packet.tilt;
    }

    static TurretPacket createAimPacket(uint8_t pan, uint8_t tilt) {
        TurretPacket packet;
        packet.header = PACKET_HEADER;
        packet.command = TurretCommand::AIM;
        packet.pan = std::min(pan, static_cast<uint8_t>(180));
        packet.tilt = std::min(tilt, static_cast<uint8_t>(180));
        packet.checksum = calculateChecksum(packet);
        return packet;
    }

    static TurretPacket createFirePacket() {
        TurretPacket packet;
        packet.header = PACKET_HEADER;
        packet.command = TurretCommand::FIRE;
        packet.pan = 90;
        packet.tilt = 90;
        packet.checksum = calculateChecksum(packet);
        return packet;
    }

    static bool validatePacket(const TurretPacket& packet) {
        if(packet.header != PACKET_HEADER){
            return false;
        }
        return packet.checksum == calculateChecksum(packet);
    }
    
};

#endif