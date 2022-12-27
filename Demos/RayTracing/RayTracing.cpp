#include <iostream>
#include <spdlog/spdlog.h>
#include <filesystem>
#include <SFML/Graphics.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "RayTracing.h"

using namespace std;

int main(int argc, char** argv){

    //Logger
    spdlog::set_pattern("[%Y-%m-%d %T] [%^%l%$] %v");

    // Image
    RenderConfig conf;
    loadRenderConfig(conf);

    unsigned char* imageData = new unsigned char[conf.renderHeight * conf.renderWidth * 3];

    // World
    ObjectList world;
    world = part_one_final_scene();

    // Camera
    Vec3 lookfrom(13, 2, 3);
    Vec3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;
    Camera cam(lookfrom, lookat, vup, 20, conf.aspectRatio, aperture, dist_to_focus);

    // Render
    spdlog::info("Render settings:");
    spdlog::info("Image size: {0:d}x{1:d}", conf.renderWidth, conf.renderHeight);
    spdlog::info("Samples per pixel: {0:d}", conf.samples_per_pixel);
    spdlog::info("Ray max depth: {0:d}", conf.max_depth);
    spdlog::info("Image output folder: {0}", conf.outPath);

    spdlog::info("Start Rendering");

    Renderer render(conf);
    render.setCamera(cam);

    render.render(imageData, world);

    spdlog::info("Render finshed.");

    time_t now = time(NULL);
    tm tm_t;
    localtime_s(&tm_t, &now);
	std::stringstream ss;
	ss << tm_t.tm_year + 1900 << "-" << tm_t.tm_mon + 1 << "-" << tm_t.tm_mday
	    << "-" << tm_t.tm_hour << "-" << tm_t.tm_min << "-" << tm_t.tm_sec << ".png";
    
    filesystem::path confPath(conf.outPath);
    filesystem::path out = confPath / ss.str();

    spdlog::info("Image saved to {0}", out.string());
    stbi_write_png(out.string().c_str(), conf.renderWidth, conf.renderHeight, 3, imageData, 0);
    delete imageData;

    return 0;
};