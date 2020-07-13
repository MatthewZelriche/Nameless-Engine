#include <iostream>
#include <Log.hpp>

#include "Game.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

int main() {
    Game game;
    game.Run();

    return 0;
}