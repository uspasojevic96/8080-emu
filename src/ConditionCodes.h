#ifndef CONDITIONCODES_H
#define CONDITIONCODES_H
#include <cstdint>

class ConditionCodes {
    public:
        std::uint8_t z:1;
        std::uint8_t s:1;
        std::uint8_t p:1;
        std::uint8_t cy:1;
        std::uint8_t ac:1;
        std::uint8_t pad:3;

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
