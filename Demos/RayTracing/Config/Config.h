#pragma once
#include <iostream>

struct RenderConfig
{
    double aspectRatio = 1.0;
    int renderWidth = 320;
    int renderHeight = 320;
    std::string outPath = "defalt";
    int samples_per_pixel = 50;
    int max_depth = 50;
};

void loadRenderConfig(RenderConfig& conf);