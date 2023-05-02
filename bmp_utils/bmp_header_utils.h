#include "bmp_types.h"
#ifndef BMP_HEADER_UTILS_H
#define BMP_HEADER_UTILS_H

#include <stdio.h>

BITMAPFILEHEADER *read_bmp_header(FILE *fp);

void write_bmp_header(FILE *fp, BITMAPFILEHEADER *header);

void print_bmp_header(BITMAPFILEHEADER *header);

BITMAPINFOHEADER *read_bmp_info_header(FILE *fp);

void print_bmp_info_header(BITMAPINFOHEADER *info_header);

void write_bmp_info_header(FILE *fp, BITMAPINFOHEADER *info_header);

#endif
