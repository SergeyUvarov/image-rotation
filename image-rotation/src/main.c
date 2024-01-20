#include <stdio.h>
#include "bmp_image.h"
#include "rotate_image.h"

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning

    if (argc >= 3)
    {
        struct image img, rotImg;

        readBmp(argv[1], &img);

        rotImg = rotate(img);

        saveBmp(argv[2], &rotImg);

        imgRelease(&img);
        imgRelease(&rotImg);

        printf("%s -> %s\n", argv[1], argv[2]);
    }
    return 0;
}
