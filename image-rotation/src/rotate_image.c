#include "rotate_image.h"

struct image rotate(struct image const source)
{
	struct image rotImg;

	imgCreate(&rotImg, source.height, source.width);

	for (uint64_t x = 0; x < rotImg.width; x++)
	{
		for (uint64_t y = 0; y < rotImg.height; y++)
		{
			*getPixel(&rotImg, x, rotImg.height - y - 1) = *getPixel(&source, y, x);
		}
	}

	return rotImg;
}