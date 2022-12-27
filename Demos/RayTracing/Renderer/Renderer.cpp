#include "Renderer.h"

#include <spdlog/spdlog.h>

Renderer::Renderer()
{
}

Renderer::Renderer(RenderConfig conf): r_conf(conf)
{
}

Renderer::~Renderer()
{
}

void Renderer::reSize(int width, int height)
{
	r_conf.renderHeight = height;
	r_conf.renderWidth = width;
}

void Renderer::render(unsigned char* data, ObjectList &world)
{
    for (size_t i = 0; i < r_conf.renderHeight; ++i)
    {
        spdlog::info("Rendered {0:d}/{1:d}", i, r_conf.renderHeight);

        for (size_t j = 0; j < r_conf.renderWidth; ++j)
        {
            Color pixel_color(0, 0, 0);
            for (size_t s = 0; s < r_conf.samples_per_pixel; ++s)
            {

                double u = double(j + random_double()) / (r_conf.renderWidth - 1);
                double v = double(i + random_double()) / (r_conf.renderHeight - 1);

                Ray r = r_cam.getRay(u, v);

                pixel_color += rayColor(r, world, r_conf.max_depth);
            };

            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            double scale = 1.0 / r_conf.samples_per_pixel;
            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write color
            data[r_conf.renderWidth * (r_conf.renderHeight - i - 1) * 3 + j * 3 + 0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
            data[r_conf.renderWidth * (r_conf.renderHeight - i - 1) * 3 + j * 3 + 1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
            data[r_conf.renderWidth * (r_conf.renderHeight - i - 1) * 3 + j * 3 + 2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
        }
    };
}

void Renderer::setCamera(Camera camera)
{
    r_cam = camera;
}

Color rayColor(const Ray& r, const Object& world, int depth) {
    HitInfo info;

    if (depth <= 0) return Color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, info)) {
        Ray scattered;
        Color attenuation;
        if (info.mat_ptr->scatter(r, info, attenuation, scattered))
            return attenuation * rayColor(scattered, world, depth - 1);
        return Color(0, 0, 0);
    };

    Vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
};
