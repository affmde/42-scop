#include "Display.hpp"

#include <iostream>

Display::Display() {}

void Display::init(int width, int heigth, const std::vector<Face *> &faces)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	this->mlx = mlx_init(width, heigth, "42-scop", false);
	if (!this->mlx)
		throw std::runtime_error("Failed to initialize mlx");
	int w, h;
	mlx_get_monitor_size(0, &w, &h);
	this->img = mlx_new_image(mlx, w, h);

	//mlx_put_pixel(this->img, width * 0.5f, heigth * 0.5f, 0xFFFFFF);
	this->drawFace(faces);
	mlx_image_to_window(this->mlx, this->img, 0, 0);
	mlx_loop_hook(this->mlx, hook, this->mlx);
	mlx_loop(this->mlx);
	mlx_terminate(this->mlx);
}

void Display::hook(void* param)
{
	const mlx_t* mlx = (mlx_t*)param;
	(void)mlx;
}

void Display::drawFace(const std::vector<Face *> &faces)
{
	for(auto &face : faces)
	{
		for(auto &v : face->getV())
		{
			mlx_put_pixel(this->img, 1900 * 0.5f + v.getX() * 250, 1080 * 0.5f - v.getY() * 250, 0xFFFFFF);
		}
	}
}
