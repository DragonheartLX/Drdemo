#pragma once
#include "Ray/Ray.h"
#include "Object/Object.h"
#include "Color/Color.h"
#include "Object/Object.h"

struct HitInfo;

Vec3 reflect(const Vec3 &v, const Vec3 &n);
Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);

class Material
{
public:
    Material();
    ~Material();

    virtual bool scatter(const Ray &r_in, const HitInfo &rec, Color &attenuation, Ray &scattered) const = 0;
};

class lambertian : public Material
{
public:
    lambertian(const Color &a) : albedo(a) {}

    virtual bool scatter(const Ray &r_in, const HitInfo &rec, Color &attenuation, Ray &scattered) const override;

public:
    Color albedo;
};

class Metal : public Material
{
public:
    Metal(const Color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray &r_in, const HitInfo &rec, Color &attenuation, Ray &scattered) const override;

public:
    Color albedo;
    double fuzz;
};

class dielectric : public Material {
    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(const Ray& r_in, const HitInfo& rec, Color& attenuation, Ray& scattered) const override;

    public:
        double ir; // Index of Refraction

    private:
       static double reflectance(double cosine, double ref_idx);
};
