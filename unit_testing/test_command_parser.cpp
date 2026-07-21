#include <iostream>
#include <cstdint>

#include "../turret_Uno/CommandParser.h"

struct TestResults {
    uint32_t testsExecuted;
    uint32_t testsPassed;
    uint32_t testsFailed;
};

static void assertCondition(bool Condition, const char* testName, TestResults& results){
    results.testsExecuted += 1;
    if(Condition){
        results.testsPassed += 1;
        std::cout << "[PASS] " << testName << "\n";
    } else {
        results.testsFailed += 1;
        std::cout << "[FAILED] " << testName << "\n";
    }
}

int main() {
    TestResults results = {0, 0, 0};

    std::cout << "_____________________________________________\n";
    std::cout << "             ᓚ₍ ^. ̫ .^₎▄︻デ══━一            \n";
    std::cout << "   Mess with the Cat, Prepare for the Gat    \n";
    std::cout << "          -- Parser Unit Testing --          \n";
    std::cout << "_____________________________________________\n\n";


    // Test 1: Packet Memory Layout Fixed at 5 Bytes
    assertCondition(
        sizeof(TurretPacket) == 5, 
        "REQ-01: Packet Memory Layout Fixed at 5 Bytes",
        results
    );
    

    // Test 2: Nominal Aim Packet Generation & Checksum Verification
    TurretPacket aimPacket = CommandParser::createAimPacket(120, 45);

    bool isAimValid = 
                    (aimPacket.header == PACKET_HEADER) &&
                    (aimPacket.command == TurretCommand::AIM) &&
                    (aimPacket.pan == 120) &&
                    (aimPacket.tilt == 45) &&
                    CommandParser::validatePacket(aimPacket);
    
    assertCondition(
        isAimValid,
        "REQ-02: Nominal Aim Packet Data & Checksum Verification",
        results
    );


    // Test 3: Defensive Rejection of Corrupted Data
    TurretPacket malformedPacket = aimPacket;
    malformedPacket.pan = -360; // introducing malformed telemetry
    
    assertCondition(
        CommandParser::validatePacket(malformedPacket) == false,
        "REQ-03: Defensive Rejection of Corrupted Data",
        results
    );


    // Test 4: Boundary & Safety limits Check + Verify out-of-bounds inputs do not exceed hardware limits
    TurretPacket outOfBoundsPacket = CommandParser::createAimPacket(250, 200);
    bool boundaryClamped = (outOfBoundsPacket.pan <= 180) && (outOfBoundsPacket.tilt <= 180);
    assertCondition(
        boundaryClamped,
        "REQ-04: Software Telemetry Clamping within Physical Bounds",
        results
    );
    

    // Test Summary + Deterministic Return
    std::cout << "\n_____________________________________________\n";
    std::cout << "\n                  Test Summary               \n";
    std::cout << "\n_____________________________________________\n";
    std::cout << "\n                  ≽^•⩊•^≼                   \n";
    std::cout << "               Executed: " << results.testsExecuted << "\n";
    std::cout << "                 Passed: " << results.testsPassed << "\n";
    std::cout << "                 Failed: " << results.testsFailed << "\n";
    std::cout << "\n_____________________________________________\n\n";

    return (results.testsFailed == 0) ? 0 : 1;
}