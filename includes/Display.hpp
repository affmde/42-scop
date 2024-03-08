#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <MLX42/MLX42.h>
#include <vector>
#include "Face.hpp"

class Display
{
public:
	Display();
	~Display() {}

	void init(int width, int height, const std::vector<Face *> &faces);
	static void hook(void *param);

	void drawFace(const std::vector<Face *> &faces);

private:
	mlx_t *mlx;
	mlx_image_t *img;
};

#endif