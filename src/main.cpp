#include <CPU.h>
#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Hello" << std::endl;

    CPU cpu;
    cpu.run();

    return EXIT_SUCCESS;
}
