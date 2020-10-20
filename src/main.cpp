#include <cstdlib>
#include <iostream>
#include <ConditionCodes.h>
#include <State.h>

int main() {
    std::cout << "Hello" << std::endl;

    State state{
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        ConditionCodes{1,1,1,1,1,3},
        0
    };

    std::cout << state.cc.pad << std::endl;
    return EXIT_SUCCESS;
}
