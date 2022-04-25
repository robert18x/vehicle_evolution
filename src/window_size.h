#pragma once

struct WindowSize {
    constexpr WindowSize(int width, int height) : width(width), height(height) {}
    int width;
    int height;
};
