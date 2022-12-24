#include <iostream>
#include <spdlog/spdlog.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "RayTracing.h"

using namespace std;

Color rayColor(const Ray& r, const Object& world, int depth);

int main(int argc, char** argv){

    //Logger
    spdlog::set_pattern("[%Y-%m-%d %T] [%^%l%$] %v");

    // Image
    RenderConfig conf;
    loadRenderConfig(conf);
    /*
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 1280;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    string outPath;
    int samples_per_pixel = 50;
    int max_depth = 50;
    */
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

    spdlog::info("Start Rendering");
    time_t startTime = time(NULL);

    for (size_t i = 0; i < conf.renderHeight; ++i)
    {
        time_t renderTime = time(NULL);
        time_t used = renderTime - startTime;
        tm* u_t = localtime(&used);

        // Time difference UTC+8 so need t_t->tm_hour - 8
        spdlog::info("Rendered ({0:d}/{1:d}) have used {2:d} hours {3:d} minutes {4:d} seconds", i, conf.renderHeight, u_t->tm_hour - 8, u_t->tm_min, u_t->tm_sec);
        for (size_t j = 0; j < conf.renderWidth; ++j)
        {
            Color pixel_color(0, 0, 0);
            for (size_t s = 0; s < conf.samples_per_pixel; ++s)
            {
                
                double u = double(j + random_double()) / (conf.renderWidth-1);
                double v = double(i + random_double()) / (conf.renderHeight-1);
                
                Ray r = cam.getRay(u, v);

                pixel_color += rayColor(r, world, conf.max_depth);
            };

            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            double scale = 1.0 / conf.samples_per_pixel;
            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write color
            imageData[conf.renderWidth * (conf.renderHeight - i - 1) * 3 + j * 3 + 0] = static_cast<int>(256 * clamp(r, 0.0, 0.999)); 
            imageData[conf.renderWidth * (conf.renderHeight - i - 1) * 3 + j * 3 + 1] = static_cast<int>(256 * clamp(g, 0.0, 0.999)); 
            imageData[conf.renderWidth * (conf.renderHeight - i - 1) * 3 + j * 3 + 2] = static_cast<int>(256 * clamp(b, 0.0, 0.999)); 
        }
    };
    spdlog::info("Render finshed.");

    time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	std::stringstream ss;
	ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday
	    << "-" << tm_t->tm_hour << "-" << tm_t->tm_min << "-" << tm_t->tm_sec << ".png";
    
    conf.outPath = ss.str();

    time_t total_t = now - startTime;
    tm* t_t = localtime(&total_t);
    // Time difference UTC+8 so need t_t->tm_hour - 8
    spdlog::info("Render used {0:d} hours {1:d} minutes {2:d} seconds", t_t->tm_hour - 8, t_t->tm_min, t_t->tm_sec);
    spdlog::info("Image saved to {0}", conf.outPath);
    stbi_write_png(conf.outPath.c_str(), conf.renderWidth, conf.renderHeight, 3, imageData, 0);
    delete imageData;

    return 0;
};

Color rayColor(const Ray& r, const Object& world, int depth) {
    HitInfo info;

    if (depth <= 0) return Color(0, 0, 0);
    
    if (world.hit(r, 0.001, infinity, info)){
        Ray scattered;
        Color attenuation;
        if (info.mat_ptr->scatter(r, info, attenuation, scattered))
            return attenuation * rayColor(scattered, world, depth - 1);
        return Color(0, 0, 0);
    };
    
    Vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
};