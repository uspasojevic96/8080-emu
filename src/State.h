#include <cstdint>
#include <ConditionCodes.h>
class State {
    public:
        std::uint8_t a;
        std::uint8_t b;
        std::uint8_t c;
        std::uint8_t d;
        std::uint8_t e;
        std::uint8_t h;
        std::uint8_t l;
        std::uint16_t sp;
        std::uint16_t pc;
        std::uint8_t* memory;
        ConditionCodes cc;
        std::uint8_t int_enable;

        State(std::uint8_t _a,
              std::uint8_t _b,
              std::uint8_t _c,
              std::uint8_t _d,
              std::uint8_t _e,
              std::uint8_t _h,
              std::uint8_t _l,
              std::uint16_t _sp,
              std::uint16_t _pc,
              std::uint8_t* _memory,
              ConditionCodes _cc,
              std::uint8_t _int_enable) :
            a{_a},
            b{_b},
            c{_c},
            d{_d},
            e{_e},
            h{_h},
            l{_l},
            sp{_sp},
            pc{_pc},
            memory{_memory},
            cc{_cc},
            int_enable{_int_enable}
    {}
};
