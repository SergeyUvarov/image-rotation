#include "bmp_image.h"

enum read_status from_bmp( FILE* in, struct image* img )
{
	struct bmp_header header;
	fread(&header, sizeof(header), 1, in);
	if (header.bfType != 0x4D42) return READ_INVALID_SIGNATURE;
	if (header.bOffBits != 54 || header.biSize != 40 || header.biBitCount != 24) return READ_INVALID_HEADER;

	imgCreate(img, header.biWidth, header.biHeight);

	uint64_t lineByteSize = (img->width * 3 + 3) / 4 * 4;

	uint8_t trashbytes[4];
	for (uint64_t line = 0; line < img->height; line++) {
		uint64_t offset = line * img->width;
		if (fread(img->data + offset, 3, img->width, in) != img->width)
		{
			return READ_INVALID_BITS;
		}
		fread(trashbytes, 1, lineByteSize - img->width * 3, in);
	}

	return READ_OK;
}


enum write_status to_bmp( FILE* out, struct image const* img )
{
	struct bmp_header header;

	uint64_t lineByteSize = (img->width * 3 + 3) / 4 * 4;

	header.bfType = 0x4D42;
	header.bfileSize = sizeof(header) + lineByteSize * img->height;
	header.bfReserved = 0;
	header.bOffBits = 54;
	header.biSize = 40;
	header.biWidth = img->width;
	header.biHeight = img->height;
	header.biPlanes = 1;
	header.biBitCount = 24;
	header.biCompression = 0;
	header.biSizeImage = lineByteSize * img->height;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	header.biClrUsed = 0;
	header.biClrImportant = 0;

	fwrite(&header, sizeof(header), 1, out);

	uint8_t trashbytes[4];
	for(uint64_t line = 0; line < img->height; line++) {
		uint64_t offset = line * img->width;
		fwrite(img->data+offset, 3, img->width, out);
		fwrite(trashbytes, 1, lineByteSize - img->width*3, out);
	}

	return WRITE_OK;
}

enum read_status readBmp(const char* fileName, struct image* img) {
	FILE* f;
	f = fopen(fileName, "rb");
	if (!f) return READ_FILE_OPEN_ERROR;
	enum read_status rs = from_bmp(f, img);
	fclose(f);
	return rs;
}

enum write_status saveBmp(const char* fileName, struct image* img) {
	FILE* f;
	f = fopen(fileName, "wb");
	if(!f) return WRITE_FILE_OPEN_ERROR;
	enum write_status ws = to_bmp(f, img);
	fclose(f);
	return ws;
}