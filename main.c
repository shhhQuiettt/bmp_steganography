#include "bmp_header_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct CmdArgs {
  char *input_file;
  char *output_file;
};

struct Pixel {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) {
    fprintf(stderr, "Error opening file %s", filename);
    exit(1);
  }
  return fp;
}

void grayLine(uint8_t *lineBuffer, size_t bytesToGray) {
  if (bytesToGray % 3 != 0) {
    fprintf(stderr, "Error: amount of bytes to gray is not divisible by 3");
    exit(1);
  }

  for (int i = 0; i + 3 <= bytesToGray; i += 3) {
      uint8_t pixelAvg = (lineBuffer[i] + lineBuffer[i + 1] + lineBuffer[i + 2]) / 3;
      lineBuffer[i] = pixelAvg;
      lineBuffer[i + 1] = pixelAvg;
      lineBuffer[i + 2] = pixelAvg;
  }
}

int main(int argc, char *argv[]) {
  // TEMP
  char *filename = "c.bmp";
  char *output_filename = "out.bmp";

  printf("a");

  FILE *in_fp = open_file(filename, "rb");
  FILE *out_fp = open_file(output_filename, "wb");

  BITMAPFILEHEADER *header = read_bmp_header(in_fp);
  BITMAPINFOHEADER *info_header = read_bmp_info_header(in_fp);
  /* print_bmp_info_header(info_header); */
  write_bmp_header(out_fp, header);
  write_bmp_info_header(out_fp, info_header);

  size_t rowSize = info_header->biWidth * 3;
  size_t fullRowSize =
      (info_header->biBitCount * info_header->biWidth + 31) / 32 * 4;

  uint8_t *rowBuffer = malloc(sizeof(uint8_t) * fullRowSize);
  uint8_t *grayedBuffer = malloc(sizeof(uint8_t) * fullRowSize);

  while (fread(rowBuffer, fullRowSize, 1, in_fp) == 1) {
    grayLine(rowBuffer, rowSize);
    fwrite(rowBuffer, fullRowSize, 1, out_fp);
  }

  free(header);
  free(info_header);
  free(rowBuffer);
}
