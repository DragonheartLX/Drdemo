#pragma once
#include "Vec3/Vec3.h"
#include "Ray/Ray.h"
#include "Material/Material.h"

#include <memory>

class Material;

struct HitInfo
{
    Vec3 point;
    Vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal){
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};


class Object
{
public:
    Object();
    ~Object();

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitInfo& info) const = 0;
};