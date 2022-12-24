#pragma once
#include "Object/ObjectList.h"
#include "Object/Sphere.h"
#include "Material/Material.h"

ObjectList first_scene(){
    ObjectList sce;

    std::shared_ptr<lambertian> material_ground = make_shared<lambertian>(Color(0.8, 0.8, 0.0));
    std::shared_ptr<lambertian> material_center = make_shared<lambertian>(Color(0.7, 0.3, 0.3));
    std::shared_ptr<dielectric> material_left   = make_shared<dielectric>(1.5);
    std::shared_ptr<Metal> material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    sce.add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    sce.add(make_shared<Sphere>(Vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    sce.add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    sce.add(make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, material_right));

    return sce;
}

ObjectList part_one_final_scene(){
    ObjectList world;

    auto ground_material = make_shared<lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Vec3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

    return world;
}