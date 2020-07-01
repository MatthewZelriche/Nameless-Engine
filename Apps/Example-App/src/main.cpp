#include <iostream>
#include <Log.hpp>

#include "NLS-Engine/Placeholder.hpp"

int main() {
    //std::cout << "Hello world, from NamelessEngine!" << std::endl;
    NLSLOG::Info("Game", "This is a testttt");

    Placeholder placeholder;
    placeholder.Test();
    return 0;
}