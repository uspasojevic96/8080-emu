#ifndef CPU_H
#define CPU_H

#include <ConditionCodes.h>
#include <State.h>
#include <cstdlib>
#define MEMORY_SIZE 65536

class CPU {
    private:
        State state_;

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
                ConditionCodes{1,1,1,1,1,3},
                0
            }
        {};
        const State& state() noexcept;
        void unimplementedInstruction(const std::uint8_t& opcode);
        void run();
};

#endif
