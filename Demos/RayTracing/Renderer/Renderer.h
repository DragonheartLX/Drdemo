#pragma once
#include "Camera/Camera.h"
#include "Color/Color.h"
#include "Ray/Ray.h"
#include "Object/ObjectList.h"
#include "Config/Config.h"

class Renderer
{
public:
	Renderer();
	Renderer(RenderConfig conf);
	~Renderer();

	void reSize(int width, int height);
	void render(unsigned char* data, ObjectList &world);
	void setCamera(Camera camera);
private:
	RenderConfig r_conf;

	Camera r_cam;
};

Color rayColor(const Ray& r, const Object& world, int depth);