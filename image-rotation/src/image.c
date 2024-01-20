#include "image.h"

enum create_status imgCreate(struct image* img, uint64_t w, uint64_t h)
{
	img->width = w;
	img->height = h;
	img->data = (struct pixel*) malloc(w * h * sizeof(struct pixel));
	if(!img->data) return CREATE_ERROR;
	return CREATE_OK;
}


enum release_status imgRelease(struct image* img)
{
	if (!img || !img->data) return RELEASE_ERROR;
	free(img->data);
	img->data = 0;
	return RELEASE_OK;
}


struct pixel* getPixel(struct image* img, uint64_t x, uint64_t y)
{
	if(x >= img->width || y >= img->height ) return NULL;
	uint64_t idx = (y * img->width) + x;
	return &img->data[idx];
}
