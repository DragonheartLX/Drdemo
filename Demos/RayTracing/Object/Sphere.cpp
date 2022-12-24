#include "Sphere.h"

Sphere::Sphere(){

};

Sphere::~Sphere(){

};

bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitInfo& info) const {
    Vec3 oc = ray.origin() - center;
    double a = ray.direction().length_squared();
    double half_b = dot(oc, ray.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) return false;
    }
    
    info.t = root;
    info.point = ray.at(info.t);
    Vec3 outward_normal = (info.point - center) / radius;
    info.set_face_normal(ray, outward_normal);
    info.mat_ptr = mat_ptr;

    return true;
};
