#include <iostream>
#include <spdlog/spdlog.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "RayTracing.h"

using namespace std;

Color rayColor(const Ray& r);

int main(int argc, char** argv){

    // Image
    int imageHeight = 720;
    int imageWidth = 1280;
    double aspectRatio = imageWidth / imageHeight;
    string outPath;

    unsigned char* imageData = new unsigned char[imageHeight * imageWidth * 3];

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;

    Vec3 origin(0, 0, 0);
    Vec3 horizontal(viewportWidth, 0, 0);
    Vec3 vertical(0, viewportHeight, 0);
    Vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focalLength);

    // Render
    spdlog::info("Start Rendering");
    for (int i = imageHeight - 1; i >= 0; --i)
    {
        for (size_t j = 0; j < imageWidth; ++j)
        {
            double u = double(j) / (imageWidth-1);
            double v = double(i) / (imageHeight-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Color pixel_color = rayColor(r);

            // Write color
            imageData[imageWidth * (imageHeight - i - 1) * 3 + j * 3 + 0] = static_cast<int>(255.999 * pixel_color[0]); 
            imageData[imageWidth * (imageHeight - i - 1) * 3 + j * 3 + 1] = static_cast<int>(255.999 * pixel_color[1]); 
            imageData[imageWidth * (imageHeight - i - 1) * 3 + j * 3 + 2] = static_cast<int>(255.999 * pixel_color[2]); 

        }
    };
    spdlog::info("Render finshed.");

    time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	std::stringstream ss;
	ss << tm_t->tm_year + 1900 << "-" << tm_t->tm_mon + 1 << "-" << tm_t->tm_mday
	    << "-" << tm_t->tm_hour << "-" << tm_t->tm_min << "-" << tm_t->tm_sec << ".png";
    
    outPath = ss.str();

    spdlog::info("Image saved to " + outPath);
    stbi_write_png(outPath.c_str(), imageWidth, imageHeight, 3, imageData, 0);
    delete imageData;

    return 0;
};

Color rayColor(const Ray& r) {
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
};