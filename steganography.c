#include "bmp_header_utils.h"
#include <stdlib.h>

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) {
    fprintf(stderr, "Error opening file %s", filename);
    exit(1);
  }
  return fp;
}

int main(int argc, char **argv) {
  char *in_filename = "tux.bmp";
  char *out_filename = "out.bmp";

  FILE *in_fp = open_file(in_filename, "rb");
  FILE *out_fp = open_file(out_filename, "wb");

  BITMAPFILEHEADER *header = read_bmp_header(in_fp);
  BITMAPINFOHEADER *info_header = read_bmp_info_header(in_fp);

  print_bmp_header(header);
  print_bmp_info_header(info_header);

  free(header);
  free(info_header);
  fclose(in_fp);
  fclose(out_fp);
}
