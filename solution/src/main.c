#include <stdio.h>
#include "bmp_image.h"
#include "rotate_image.h"

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning

    if (argc >= 3)
    {
        struct image img, rotImg;

        if (readBmp(argv[1], &img) != READ_OK)
        {
            printf("Read error\n");
            return 0;
        }

        rotImg = rotate(img);

        if (rotImg.data == img.data)
        {
            imgRelease(&img);
            printf("Rotate error\n");
            return 0;
        }

        if (saveBmp(argv[2], &rotImg) != WRITE_OK)
        {
            imgRelease(&img);
            imgRelease(&rotImg);
            printf("Save error\n");
            return 0;
        }

        imgRelease(&img);
        imgRelease(&rotImg);
    }
    return 0;
}
