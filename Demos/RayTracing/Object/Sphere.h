#pragma once
#include "Object.h"
#include "Vec3/Vec3.h"
#include "Material/Material.h"

#include <memory>

class Sphere: public Object
{
public:
    Vec3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

    Sphere();
    Sphere(Vec3 cen, double r, std::shared_ptr<Material> m): center(cen), radius(r), mat_ptr(m) {};
    ~Sphere();

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitInfo& info) const override;
};