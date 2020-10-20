#include <CPU.h>
#include <cstdio>
#include <cstdlib>

const State& CPU::state() noexcept {
    return state_;
}

void CPU::unimplementedInstruction(const std::uint8_t& opcode) {
    ::printf("error: Unimplemented instruction 0x%02x", opcode);
    ::exit(1);
}

void CPU::run() {
    std::uint8_t opcode = state_.memory[state_.pc];

    switch(opcode) {
        case 0x00: unimplementedInstruction(opcode); break;
        case 0x01: unimplementedInstruction(opcode); break;
        case 0x02: unimplementedInstruction(opcode); break;
        case 0x03: unimplementedInstruction(opcode); break;
        case 0x04: unimplementedInstruction(opcode); break;
        case 0x05: unimplementedInstruction(opcode); break;
        case 0x06: unimplementedInstruction(opcode); break;
        case 0x07: unimplementedInstruction(opcode); break;
        case 0x09: unimplementedInstruction(opcode); break;
        case 0x0a: unimplementedInstruction(opcode); break;
        case 0x0b: unimplementedInstruction(opcode); break;
        case 0x0c: unimplementedInstruction(opcode); break;
        case 0x0d: unimplementedInstruction(opcode); break;
        case 0x0e: unimplementedInstruction(opcode); break;
        case 0x0f: unimplementedInstruction(opcode); break;
        case 0x11: unimplementedInstruction(opcode); break;
        case 0x12: unimplementedInstruction(opcode); break;
        case 0x13: unimplementedInstruction(opcode); break;
        case 0x14: unimplementedInstruction(opcode); break;
        case 0x15: unimplementedInstruction(opcode); break;
        case 0x16: unimplementedInstruction(opcode); break;
        case 0x17: unimplementedInstruction(opcode); break;
        case 0x19: unimplementedInstruction(opcode); break;
        case 0x1a: unimplementedInstruction(opcode); break;
        case 0x1b: unimplementedInstruction(opcode); break;
        case 0x1c: unimplementedInstruction(opcode); break;
        case 0x1d: unimplementedInstruction(opcode); break;
        case 0x1e: unimplementedInstruction(opcode); break;
        case 0x1f: unimplementedInstruction(opcode); break;
        case 0x21: unimplementedInstruction(opcode); break;
        case 0x22: unimplementedInstruction(opcode); break;
        case 0x23: unimplementedInstruction(opcode); break;
        case 0x24: unimplementedInstruction(opcode); break;
        case 0x25: unimplementedInstruction(opcode); break;
    }

}
