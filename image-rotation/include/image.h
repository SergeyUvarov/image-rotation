#ifndef IMG_H
#define IMG_H

#include <stdlib.h>
#include <stdint.h>

struct pixel {
uint8_t b,g,r;
};

struct image {
	uint64_t width, height;
	struct pixel *data;
};

enum create_status {
	CREATE_OK = 0,
	CREATE_ERROR
};

enum create_status imgCreate(struct image* img, uint64_t w, uint64_t h);

enum release_status {
	RELEASE_OK = 0,
	RELEASE_ERROR
};

enum release_status imgRelease(struct image* img);

struct pixel* getPixel(struct image* img, uint64_t x, uint64_t y);

#endif