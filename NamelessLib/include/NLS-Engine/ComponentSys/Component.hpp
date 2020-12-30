#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <string>
#include <stdint.h>


class NLS_API_EXPORT Component {

};

class NLS_API_EXPORT Position : Component {
public:
    float x {0};
    float y {0};
    float z {0};
};

class NLS_API_EXPORT Renderable : Component {
private:
    bool isVisible {true};
    std::string modelPath {};

public:
    std::string GetModelPath() { return modelPath; }
};

class NLS_API_EXPORT Camera : Component {
public:
    Position mCameraPos;
    float fov {80.0f};
};