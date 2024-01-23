#include "rotate_image.h"

struct image rotate(struct image source)
{
	struct image rotImg;

	if (imgCreate(&rotImg, source.height, source.width) != CREATE_OK)
	{
		return source;
	}

	for (uint64_t x = 0; x < rotImg.width; x++)
	{
		for (uint64_t y = 0; y < rotImg.height; y++)
		{
			*getPixel(&rotImg, rotImg.width - x - 1, y) = *getPixel(&source, y, x);
		}
	}

	return rotImg;
}