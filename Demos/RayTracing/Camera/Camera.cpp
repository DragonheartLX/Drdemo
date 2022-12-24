#include "Camera.h"

Camera::Camera(){
    double aspectRatio = 16.0 / 9.0;
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;

    origin = Vec3(0, 0, 0);
    horizontal = Vec3(viewportWidth, 0, 0);
    vertical = Vec3(0, viewportHeight, 0);
    lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focalLength);
};

Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist){
    double theta = degrees_to_radians(vfov);
    double h = tan(theta / 2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = aspect_ratio * viewportHeight;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewportWidth * u;
    vertical = focus_dist * viewportHeight * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;

    lens_radius = aperture / 2;
};

Camera::~Camera(){
};

Ray Camera::getRay(double s, double t) const {
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = u * rd.x() + v * rd.y();

    return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
};