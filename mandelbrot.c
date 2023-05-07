#include "bmp_utils/bmp_header_utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 100

// Function to calculate the Mandelbrot value of a given point
int mandelbrot(double x, double y) {
  double zx = 0, zy = 0;
  int iter = 0;
  while (iter < MAX_ITER && (zx * zx + zy * zy) <= 2) {
    double zx_new = zx * zx - zy * zy + x;
    zy = 2 * zx * zy + y;
    zx = zx_new;
    iter++;
  }
  return iter;
}

// Function to write a grayscale pixel to the bitmap
void write_pixel(uint8_t *bitmap, int x, int y, int width, uint8_t value) {
  int index = (y * width + x) * 3;
  bitmap[index] = value;
  bitmap[index + 1] = value;
  bitmap[index + 2] = value;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <width> <height> <output_file>\n", argv[0]);
    exit(1);
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  char *filename = argv[3];

  uint8_t *bitmap = (uint8_t *)malloc(width * height * 3);

  double x_min = -2.0, x_max = 1.0, y_min = -1.0, y_max = 1.0;
  double x_step = (x_max - x_min) / width;
  double y_step = (y_max - y_min) / height;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      double real = x * (x_max - x_min) / width + x_min;
      double imag = y * (y_max - y_min) / height + y_min;
      int iter = mandelbrot(real, imag);
      uint8_t value =
          iter == MAX_ITER ? 255 : (uint8_t)round(iter * 255.0 / MAX_ITER);
      write_pixel(bitmap, x, y, width, value);
    }
  }

  BITMAPFILEHEADER *bmp_header = malloc(sizeof(BITMAPFILEHEADER));
  bmp_header->bfType = 0x4d42;
  bmp_header->bfReserved1 = 0;
  bmp_header->bfReserved2 = 0;
  bmp_header->bfOffBits = 54;
  bmp_header->bfSize = 54 + width * height * 3;

  BITMAPINFOHEADER *bmp_info_header = malloc(sizeof(BITMAPINFOHEADER));
  bmp_info_header->biSize = 40;
  bmp_info_header->biWidth = width;
  bmp_info_header->biHeight = height;
  bmp_info_header->biPlanes = 1;
  bmp_info_header->biBitCount = 24;
  bmp_info_header->biCompression = 0;
  bmp_info_header->biSizeImage = width * height * 3;
  bmp_info_header->biXPelsPerMeter = 0;
  bmp_info_header->biYPelsPerMeter = 0;
  bmp_info_header->biClrUsed = 256;
  bmp_info_header->biClrImportant = 0;

  FILE *file = fopen(filename, "wb");

  write_bmp_header(file, bmp_header);
  write_bmp_info_header(file, bmp_info_header);

  fwrite(bitmap, sizeof(uint8_t), width * height * 3, file);
  fclose(file);

  free(bitmap);
  free(bmp_header);
  free(bmp_info_header);

  return 0;
}
