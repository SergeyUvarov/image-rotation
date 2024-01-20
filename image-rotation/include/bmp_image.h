#ifndef BMP_IMG_H
#define BMP_IMG_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include  <stdint.h>
#include "image.h"

#pragma pack(push, 1)
struct bmp_header 
{
        uint16_t bfType;
        uint32_t  bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t  biHeight;
        uint16_t  biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t  biClrImportant;
};
#pragma pack(pop)


/*  deserializer   */
enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_FILE_OPEN_ERROR
};

enum read_status from_bmp( FILE* in, struct image* img );

/*  serializer   */
enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR,
  WRITE_FILE_OPEN_ERROR
};

enum write_status to_bmp( FILE* out, struct image const* img );


enum read_status readBmp(const char* fileName, struct image* img);
enum write_status saveBmp(const char* fileName, struct image* img);



#endif