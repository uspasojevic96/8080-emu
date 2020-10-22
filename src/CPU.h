#ifndef CPU_H
#define CPU_H

#include <ConditionCodes.h>
#include <State.h>
#include <cstdlib>
#define MEMORY_SIZE 65536

class CPU {
    private:
        State state_;
        void LXI(std::uint8_t& l, std::uint8_t& r, std::uint8_t const* opcode);
        std::uint16_t makeWord(std::uint8_t l, std::uint8_t r);
        void writeWord(std::uint8_t& l, std::uint8_t& r, std::uint16_t const address);
        void INX(std::uint8_t& l, std::uint8_t& r);
        void STAX(std::uint8_t& l, std::uint8_t& r);
        void RLC();

    public:
        CPU() :
            state_{
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                (std::uint8_t*)::malloc(MEMORY_SIZE), // memory
                ConditionCodes{0,0,0,0,0,0},
                0
            }
        {};
        const State& state() noexcept;
        void unimplementedInstruction(const std::uint8_t& opcode);
        void run();
};

#endif
