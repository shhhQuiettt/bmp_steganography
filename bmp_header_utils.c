#include "bmp_header_utils.h"
#include <stdio.h>
#include <stdlib.h>

BITMAPFILEHEADER *read_bmp_header(FILE *fp) {
  BITMAPFILEHEADER *header = malloc(sizeof(BITMAPFILEHEADER));
  fread(&header->bfType, sizeof(WORD), 1, fp);
  fread(&header->bfSize, sizeof(DWORD), 1, fp);
  fread(&header->bfReserved1, sizeof(WORD), 1, fp);
  fread(&header->bfReserved2, sizeof(WORD), 1, fp);
  fread(&header->bfOffBits, sizeof(DWORD), 1, fp);
  return header;
}

void print_bmp_header(BITMAPFILEHEADER *header) {
  printf("BITMAPFILEHEADER:\n");
  printf("bfType: 0x%x\n", header->bfType);
  printf("bfSize: %d\n", header->bfSize);
  printf("bfReserved1: 0x%x\n", header->bfReserved1);
  printf("bfReserved2: 0x%x\n", header->bfReserved2);
  printf("bfOffBits: %d\n", header->bfOffBits);
}

void write_bmp_header(FILE *fp, BITMAPFILEHEADER *header) {
  fwrite(&header->bfType, sizeof(WORD), 1, fp);
  fwrite(&header->bfSize, sizeof(DWORD), 1, fp);
  fwrite(&header->bfReserved1, sizeof(WORD), 1, fp);
  fwrite(&header->bfReserved2, sizeof(WORD), 1, fp);
  fwrite(&header->bfOffBits, sizeof(DWORD), 1, fp);
}

BITMAPINFOHEADER *read_bmp_info_header(FILE *fp) {
  BITMAPINFOHEADER *header = malloc(sizeof(BITMAPINFOHEADER));
  fread(&header->biSize, sizeof(DWORD), 1, fp);
  fread(&header->biWidth, sizeof(LONG), 1, fp);
  fread(&header->biHeight, sizeof(LONG), 1, fp);
  fread(&header->biPlanes, sizeof(WORD), 1, fp);
  fread(&header->biBitCount, sizeof(WORD), 1, fp);
  fread(&header->biCompression, sizeof(DWORD), 1, fp);
  fread(&header->biSizeImage, sizeof(DWORD), 1, fp);
  fread(&header->biXPelsPerMeter, sizeof(LONG), 1, fp);
  fread(&header->biYPelsPerMeter, sizeof(LONG), 1, fp);
  fread(&header->biClrUsed, sizeof(DWORD), 1, fp);
  fread(&header->biClrImportant, sizeof(DWORD), 1, fp);
  return header;
}

void write_bmp_info_header(FILE *fp, BITMAPINFOHEADER *info_header) {
  fwrite(&info_header->biSize, sizeof(DWORD), 1, fp);
  fwrite(&info_header->biWidth, sizeof(LONG), 1, fp);
  fwrite(&info_header->biHeight, sizeof(LONG), 1, fp);
  fwrite(&info_header->biPlanes, sizeof(WORD), 1, fp);
  fwrite(&info_header->biBitCount, sizeof(WORD), 1, fp);
  fwrite(&info_header->biCompression, sizeof(DWORD), 1, fp);
  fwrite(&info_header->biSizeImage, sizeof(DWORD), 1, fp);
  fwrite(&info_header->biXPelsPerMeter, sizeof(LONG), 1, fp);
  fwrite(&info_header->biYPelsPerMeter, sizeof(LONG), 1, fp);
  fwrite(&info_header->biClrUsed, sizeof(DWORD), 1, fp);
  fwrite(&info_header->biClrImportant, sizeof(DWORD), 1, fp);
}

void print_bmp_info_header(BITMAPINFOHEADER *info_header) {
  printf("BITMAPINFOHEADER:\n");
  printf("biSize: %d\n", info_header->biSize);
  printf("biWidth: %d\n", info_header->biWidth);
  printf("biHeight: %d\n", info_header->biHeight);
  printf("biPlanes: %d\n", info_header->biPlanes);
  printf("biBitCount: %d\n", info_header->biBitCount);
  printf("biCompression: %d\n", info_header->biCompression);
  printf("biSizeImage: %d\n", info_header->biSizeImage);
  printf("biXPelsPerMeter: %d\n", info_header->biXPelsPerMeter);
  printf("biYPelsPerMeter: %d\n", info_header->biYPelsPerMeter);
  printf("biClrUsed: %d\n", info_header->biClrUsed);
  printf("biClrImportant: %d\n", info_header->biClrImportant);
}
