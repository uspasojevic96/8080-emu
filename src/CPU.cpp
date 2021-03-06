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

std::uint16_t CPU::makeWord(std::uint8_t l, std::uint8_t r) {
    return l << 8 | r;
}

void CPU::writeWord(std::uint8_t& l, std::uint8_t& r, std::uint16_t const address) {
    r = address & 0x00ff;
    l = address >> 8 & 0x00ff;
}

void CPU::LXI(std::uint8_t& l, std::uint8_t& r, std::uint8_t const* opcode) {
    l = opcode[2];
    r = opcode[1];
    state_.pc += 2;
}

void CPU::INX(std::uint8_t& l, std::uint8_t& r) {
    auto address = makeWord(l, r);
    address += 1;
    writeWord(l, r, address);
}

void CPU::STAX(std::uint8_t& l, std::uint8_t& r) {
    auto address = makeWord(l, r);
    state_.memory[address] = state_.a;
}

void CPU::RLC() {
    auto temp = state_.a;

    state_.a = temp << 1 | temp >> 7;
    state_.cc.cy = (temp >> 7) > 0 ? 1 : 0;
}

void CPU::DAD(std::uint8_t const l, std::uint8_t const r) {
    std::uint32_t hl = static_cast<std::uint32_t>(makeWord(state_.h, state_.l));
    auto pair = makeWord(l, r);

    hl = hl + pair;

    state_.cc.cy = (hl & 0xffff0000) > 0 ? 1 : 0;
    writeWord(state_.h, state_.l, static_cast<std::uint16_t>(hl & 0x0000ffff));
}

void CPU::updateArithmeticFlags(std::uint16_t const result) {
    state_.cc.z = (result & 0x00ff) == 0 ? 1 : 0;
    state_.cc.s = (result & 0x80) == 0x80 ? 1 : 0;
    state_.cc.p = checkParity(result & 0x00ff, 8) ? 1 : 0;
    state_.cc.ac = result > 0x09 ? 1 : 0;
}

bool CPU::checkParity(int number, int size) {
    int result = 0;

    for(int i = 0; i < size; i++) {
        result += number & 1;
        number = number >> 1;
    }

    return (result % 2) == 0;
}

void CPU::INR(std::uint8_t& reg) {
    std::uint16_t result = static_cast<std::uint16_t>(reg);
    reg += 1;
    result += 1;

    updateArithmeticFlags(result);
}

void CPU::DCR(std::uint8_t& reg) {
    std::uint16_t result = static_cast<std::uint16_t>(reg);
    reg -= 1;
    result -= 1;

    updateArithmeticFlags(result);
}

void CPU::run() {
    std::uint8_t *opcode = &state_.memory[state_.pc];

    switch(*opcode) {
        case 0x00:
            break;
        case 0x01:
            LXI(state_.b, state_.c, opcode);
            break;
        case 0x02:
            STAX(state_.b, state_.c);
            break;
        case 0x03:
            INX(state_.b, state_.c);
            break;
        case 0x04:
            INR(state_.b);
            break;
        case 0x05:
            DCR(state_.b);
            break;
        case 0x06:
            state_.b = opcode[1];
            state_.pc += 1;
            break;
        case 0x07:
            RLC();
            break;
        case 0x09:
            DAD(state_.b, state_.c);
            break;
        case 0x0a: unimplementedInstruction(*opcode); break;
        case 0x0b: unimplementedInstruction(*opcode); break;
        case 0x0c: unimplementedInstruction(*opcode); break;
        case 0x0d: unimplementedInstruction(*opcode); break;
        case 0x0e: unimplementedInstruction(*opcode); break;
        case 0x0f: unimplementedInstruction(*opcode); break;
        case 0x11:
            LXI(state_.d, state_.e, opcode);
            break;
        case 0x12:
            STAX(state_.d, state_.e);
            break;
        case 0x13:
            INX(state_.d, state_.e);
            break;
        case 0x14: unimplementedInstruction(*opcode); break;
        case 0x15: unimplementedInstruction(*opcode); break;
        case 0x16: unimplementedInstruction(*opcode); break;
        case 0x17: unimplementedInstruction(*opcode); break;
        case 0x19:
            DAD(state_.d, state_.e);
            break;
        case 0x1a: unimplementedInstruction(*opcode); break;
        case 0x1b: unimplementedInstruction(*opcode); break;
        case 0x1c: unimplementedInstruction(*opcode); break;
        case 0x1d: unimplementedInstruction(*opcode); break;
        case 0x1e: unimplementedInstruction(*opcode); break;
        case 0x1f: unimplementedInstruction(*opcode); break;
        case 0x21:
            LXI(state_.h, state_.l, opcode);
            break;
        case 0x22: unimplementedInstruction(*opcode); break;
        case 0x23:
            INX(state_.h, state_.l);
            break;
        case 0x24: unimplementedInstruction(*opcode); break;
        case 0x25: unimplementedInstruction(*opcode); break;
        case 0x26: unimplementedInstruction(*opcode); break;
        case 0x27: unimplementedInstruction(*opcode); break;
        case 0x29:
            DAD(state_.h, state_.l);
            break;
        case 0x2a: unimplementedInstruction(*opcode); break;
        case 0x2b: unimplementedInstruction(*opcode); break;
        case 0x2c: unimplementedInstruction(*opcode); break;
        case 0x2d: unimplementedInstruction(*opcode); break;
        case 0x2e: unimplementedInstruction(*opcode); break;
        case 0x2f: unimplementedInstruction(*opcode); break;
        case 0x31:
            state_.sp = makeWord(opcode[2], opcode[1]);
            state_.pc += 2;
            break;
        case 0x32: unimplementedInstruction(*opcode); break;
        case 0x33:
            state_.sp += 1;
            break;
        case 0x34: unimplementedInstruction(*opcode); break;
        case 0x35: unimplementedInstruction(*opcode); break;
        case 0x36: unimplementedInstruction(*opcode); break;
        case 0x37: unimplementedInstruction(*opcode); break;
        case 0x39: unimplementedInstruction(*opcode); break;
        case 0x3a: unimplementedInstruction(*opcode); break;
        case 0x3b: unimplementedInstruction(*opcode); break;
        case 0x3c: unimplementedInstruction(*opcode); break;
        case 0x3d: unimplementedInstruction(*opcode); break;
        case 0x3e: unimplementedInstruction(*opcode); break;
        case 0x3f: unimplementedInstruction(*opcode); break;
        case 0x40: unimplementedInstruction(*opcode); break;
        case 0x41: unimplementedInstruction(*opcode); break;
        case 0x42: unimplementedInstruction(*opcode); break;
        case 0x43: unimplementedInstruction(*opcode); break;
        case 0x44: unimplementedInstruction(*opcode); break;
        case 0x45: unimplementedInstruction(*opcode); break;
        case 0x46: unimplementedInstruction(*opcode); break;
        case 0x47: unimplementedInstruction(*opcode); break;
        case 0x48: unimplementedInstruction(*opcode); break;
        case 0x49: unimplementedInstruction(*opcode); break;
        case 0x4a: unimplementedInstruction(*opcode); break;
        case 0x4b: unimplementedInstruction(*opcode); break;
        case 0x4c: unimplementedInstruction(*opcode); break;
        case 0x4d: unimplementedInstruction(*opcode); break;
        case 0x4e: unimplementedInstruction(*opcode); break;
        case 0x4f: unimplementedInstruction(*opcode); break;
        case 0x50: unimplementedInstruction(*opcode); break;
        case 0x51: unimplementedInstruction(*opcode); break;
        case 0x52: unimplementedInstruction(*opcode); break;
        case 0x53: unimplementedInstruction(*opcode); break;
        case 0x54: unimplementedInstruction(*opcode); break;
        case 0x55: unimplementedInstruction(*opcode); break;
        case 0x56: unimplementedInstruction(*opcode); break;
        case 0x57: unimplementedInstruction(*opcode); break;
        case 0x58: unimplementedInstruction(*opcode); break;
        case 0x59: unimplementedInstruction(*opcode); break;
        case 0x5a: unimplementedInstruction(*opcode); break;
        case 0x5b: unimplementedInstruction(*opcode); break;
        case 0x5c: unimplementedInstruction(*opcode); break;
        case 0x5d: unimplementedInstruction(*opcode); break;
        case 0x5e: unimplementedInstruction(*opcode); break;
        case 0x5f: unimplementedInstruction(*opcode); break;
        case 0x60: unimplementedInstruction(*opcode); break;
        case 0x61: unimplementedInstruction(*opcode); break;
        case 0x62: unimplementedInstruction(*opcode); break;
        case 0x63: unimplementedInstruction(*opcode); break;
        case 0x64: unimplementedInstruction(*opcode); break;
        case 0x65: unimplementedInstruction(*opcode); break;
        case 0x66: unimplementedInstruction(*opcode); break;
        case 0x67: unimplementedInstruction(*opcode); break;
        case 0x68: unimplementedInstruction(*opcode); break;
        case 0x69: unimplementedInstruction(*opcode); break;
        case 0x6a: unimplementedInstruction(*opcode); break;
        case 0x6b: unimplementedInstruction(*opcode); break;
        case 0x6c: unimplementedInstruction(*opcode); break;
        case 0x6d: unimplementedInstruction(*opcode); break;
        case 0x6e: unimplementedInstruction(*opcode); break;
        case 0x6f: unimplementedInstruction(*opcode); break;
        case 0x70: unimplementedInstruction(*opcode); break;
        case 0x71: unimplementedInstruction(*opcode); break;
        case 0x72: unimplementedInstruction(*opcode); break;
        case 0x73: unimplementedInstruction(*opcode); break;
        case 0x74: unimplementedInstruction(*opcode); break;
        case 0x75: unimplementedInstruction(*opcode); break;
        case 0x76: unimplementedInstruction(*opcode); break;
        case 0x77: unimplementedInstruction(*opcode); break;
        case 0x78: unimplementedInstruction(*opcode); break;
        case 0x79: unimplementedInstruction(*opcode); break;
        case 0x7a: unimplementedInstruction(*opcode); break;
        case 0x7b: unimplementedInstruction(*opcode); break;
        case 0x7c: unimplementedInstruction(*opcode); break;
        case 0x7d: unimplementedInstruction(*opcode); break;
        case 0x7e: unimplementedInstruction(*opcode); break;
        case 0x7f: unimplementedInstruction(*opcode); break;
        case 0x80: unimplementedInstruction(*opcode); break;
        case 0x81: unimplementedInstruction(*opcode); break;
        case 0x82: unimplementedInstruction(*opcode); break;
        case 0x83: unimplementedInstruction(*opcode); break;
        case 0x84: unimplementedInstruction(*opcode); break;
        case 0x85: unimplementedInstruction(*opcode); break;
        case 0x86: unimplementedInstruction(*opcode); break;
        case 0x87: unimplementedInstruction(*opcode); break;
        case 0x88: unimplementedInstruction(*opcode); break;
        case 0x89: unimplementedInstruction(*opcode); break;
        case 0x8a: unimplementedInstruction(*opcode); break;
        case 0x8b: unimplementedInstruction(*opcode); break;
        case 0x8c: unimplementedInstruction(*opcode); break;
        case 0x8d: unimplementedInstruction(*opcode); break;
        case 0x8e: unimplementedInstruction(*opcode); break;
        case 0x8f: unimplementedInstruction(*opcode); break;
        case 0x90: unimplementedInstruction(*opcode); break;
        case 0x91: unimplementedInstruction(*opcode); break;
        case 0x92: unimplementedInstruction(*opcode); break;
        case 0x93: unimplementedInstruction(*opcode); break;
        case 0x94: unimplementedInstruction(*opcode); break;
        case 0x95: unimplementedInstruction(*opcode); break;
        case 0x96: unimplementedInstruction(*opcode); break;
        case 0x97: unimplementedInstruction(*opcode); break;
        case 0x98: unimplementedInstruction(*opcode); break;
        case 0x99: unimplementedInstruction(*opcode); break;
        case 0x9a: unimplementedInstruction(*opcode); break;
        case 0x9b: unimplementedInstruction(*opcode); break;
        case 0x9c: unimplementedInstruction(*opcode); break;
        case 0x9d: unimplementedInstruction(*opcode); break;
        case 0x9e: unimplementedInstruction(*opcode); break;
        case 0x9f: unimplementedInstruction(*opcode); break;
        case 0xa0: unimplementedInstruction(*opcode); break;
        case 0xa1: unimplementedInstruction(*opcode); break;
        case 0xa2: unimplementedInstruction(*opcode); break;
        case 0xa3: unimplementedInstruction(*opcode); break;
        case 0xa4: unimplementedInstruction(*opcode); break;
        case 0xa5: unimplementedInstruction(*opcode); break;
        case 0xa6: unimplementedInstruction(*opcode); break;
        case 0xa7: unimplementedInstruction(*opcode); break;
        case 0xa8: unimplementedInstruction(*opcode); break;
        case 0xa9: unimplementedInstruction(*opcode); break;
        case 0xaa: unimplementedInstruction(*opcode); break;
        case 0xab: unimplementedInstruction(*opcode); break;
        case 0xac: unimplementedInstruction(*opcode); break;
        case 0xad: unimplementedInstruction(*opcode); break;
        case 0xae: unimplementedInstruction(*opcode); break;
        case 0xaf: unimplementedInstruction(*opcode); break;
        case 0xb0: unimplementedInstruction(*opcode); break;
        case 0xb1: unimplementedInstruction(*opcode); break;
        case 0xb2: unimplementedInstruction(*opcode); break;
        case 0xb3: unimplementedInstruction(*opcode); break;
        case 0xb4: unimplementedInstruction(*opcode); break;
        case 0xb5: unimplementedInstruction(*opcode); break;
        case 0xb6: unimplementedInstruction(*opcode); break;
        case 0xb7: unimplementedInstruction(*opcode); break;
        case 0xb8: unimplementedInstruction(*opcode); break;
        case 0xb9: unimplementedInstruction(*opcode); break;
        case 0xba: unimplementedInstruction(*opcode); break;
        case 0xbb: unimplementedInstruction(*opcode); break;
        case 0xbc: unimplementedInstruction(*opcode); break;
        case 0xbd: unimplementedInstruction(*opcode); break;
        case 0xbe: unimplementedInstruction(*opcode); break;
        case 0xbf: unimplementedInstruction(*opcode); break;
        case 0xc0: unimplementedInstruction(*opcode); break;
        case 0xc1: unimplementedInstruction(*opcode); break;
        case 0xc2: unimplementedInstruction(*opcode); break;
        case 0xc3: unimplementedInstruction(*opcode); break;
        case 0xc4: unimplementedInstruction(*opcode); break;
        case 0xc5: unimplementedInstruction(*opcode); break;
        case 0xc6: unimplementedInstruction(*opcode); break;
        case 0xc7: unimplementedInstruction(*opcode); break;
        case 0xc8: unimplementedInstruction(*opcode); break;
        case 0xc9: unimplementedInstruction(*opcode); break;
        case 0xca: unimplementedInstruction(*opcode); break;
        case 0xcc: unimplementedInstruction(*opcode); break;
        case 0xcd: unimplementedInstruction(*opcode); break;
        case 0xce: unimplementedInstruction(*opcode); break;
        case 0xcf: unimplementedInstruction(*opcode); break;
        case 0xd0: unimplementedInstruction(*opcode); break;
        case 0xd1: unimplementedInstruction(*opcode); break;
        case 0xd2: unimplementedInstruction(*opcode); break;
        case 0xd3: unimplementedInstruction(*opcode); break;
        case 0xd4: unimplementedInstruction(*opcode); break;
        case 0xd5: unimplementedInstruction(*opcode); break;
        case 0xd6: unimplementedInstruction(*opcode); break;
        case 0xd7: unimplementedInstruction(*opcode); break;
        case 0xd8: unimplementedInstruction(*opcode); break;
        case 0xda: unimplementedInstruction(*opcode); break;
        case 0xdb: unimplementedInstruction(*opcode); break;
        case 0xdc: unimplementedInstruction(*opcode); break;
        case 0xde: unimplementedInstruction(*opcode); break;
        case 0xdf: unimplementedInstruction(*opcode); break;
        case 0xe0: unimplementedInstruction(*opcode); break;
        case 0xe1: unimplementedInstruction(*opcode); break;
        case 0xe2: unimplementedInstruction(*opcode); break;
        case 0xe3: unimplementedInstruction(*opcode); break;
        case 0xe4: unimplementedInstruction(*opcode); break;
        case 0xe5: unimplementedInstruction(*opcode); break;
        case 0xe6: unimplementedInstruction(*opcode); break;
        case 0xe7: unimplementedInstruction(*opcode); break;
        case 0xe8: unimplementedInstruction(*opcode); break;
        case 0xe9: unimplementedInstruction(*opcode); break;
        case 0xea: unimplementedInstruction(*opcode); break;
        case 0xeb: unimplementedInstruction(*opcode); break;
        case 0xec: unimplementedInstruction(*opcode); break;
        case 0xee: unimplementedInstruction(*opcode); break;
        case 0xef: unimplementedInstruction(*opcode); break;
        case 0xf0: unimplementedInstruction(*opcode); break;
        case 0xf1: unimplementedInstruction(*opcode); break;
        case 0xf2: unimplementedInstruction(*opcode); break;
        case 0xf3: unimplementedInstruction(*opcode); break;
        case 0xf4: unimplementedInstruction(*opcode); break;
        case 0xf5: unimplementedInstruction(*opcode); break;
        case 0xf6: unimplementedInstruction(*opcode); break;
        case 0xf7: unimplementedInstruction(*opcode); break;
        case 0xf8: unimplementedInstruction(*opcode); break;
        case 0xf9: unimplementedInstruction(*opcode); break;
        case 0xfa: unimplementedInstruction(*opcode); break;
        case 0xfb: unimplementedInstruction(*opcode); break;
        case 0xfc: unimplementedInstruction(*opcode); break;
        case 0xfe: unimplementedInstruction(*opcode); break;
        case 0xff: unimplementedInstruction(*opcode); break;
    }

    state_.pc += 1;

}
