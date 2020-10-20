#ifndef CONDITIONCODES_H
#define CONDITIONCODES_H
#include <cstdint>

class ConditionCodes {
    public:
        std::uint8_t z;
        std::uint8_t s;
        std::uint8_t p;
        std::uint8_t cy;
        std::uint8_t ac;
        std::uint8_t pad;

    ConditionCodes(std::uint8_t _z,
                   std::uint8_t _s,
                   std::uint8_t _p,
                   std::uint8_t _cy,
                   std::uint8_t _ac,
                   std::uint8_t _pad) : 
        z{_z},
        s{_s},
        p{_p},
        cy{_cy},
        ac{_ac},
        pad{_pad}
    {}
};
#endif
