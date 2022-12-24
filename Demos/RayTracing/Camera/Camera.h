#pragma once
#include "Vec3/Vec3.h"
#include "Ray/Ray.h"

class Camera
{
private:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;

public:
    Camera();
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);
    ~Camera();

    Ray getRay(double u, double v) const;
};