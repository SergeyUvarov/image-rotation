#include "bmp_image.h"

enum read_status from_bmp( FILE* in, struct image* img )
{
	struct bmp_header header;
	if (fread(&header, sizeof(header), 1, in) != 1) return READ_INVALID_BITS;
	if (header.bfType != 0x4D42) return READ_INVALID_SIGNATURE;
	if (header.bOffBits != 54 || header.biSize != 40 || header.biBitCount != 24) return READ_INVALID_HEADER;

	if (imgCreate(img, header.biWidth, header.biHeight) != CREATE_OK)
	{
		return READ_CREATE_ERROR;
	}

	uint64_t lineByteSize = (img->width * 3 + 3) / 4 * 4;

	uint32_t trashbytes = 0;
	for (uint64_t line = 0; line < img->height; line++) {
		uint64_t offset = line * img->width;
		if (fread(img->data + offset, 3, img->width, in) != img->width)
		{
			imgRelease(img);
			return READ_INVALID_BITS;
		}
		if (fread(&trashbytes, 1, lineByteSize - img->width * 3, in) != lineByteSize - img->width * 3)
		{
			imgRelease(img);
			return READ_INVALID_BITS;
		}
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

	if(fwrite(&header, sizeof(header), 1, out) != 1) return WRITE_ERROR;

	uint32_t trashbytes = 0;
	for(uint64_t line = 0; line < img->height; line++) {
		uint64_t offset = line * img->width;
		if(fwrite(img->data+offset, 3, img->width, out) != img->width) return WRITE_ERROR;
		if(fwrite(&trashbytes, 1, lineByteSize - img->width*3, out) != lineByteSize - img->width * 3)  return WRITE_ERROR;
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