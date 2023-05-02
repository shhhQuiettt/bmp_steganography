#include "histogram.h"
#include <stdio.h>

unsigned int sumPixels(unsigned int pixelHistogram[16]) {
  unsigned int sum = 0;
  for (int i = 0; i < 16; i++) {
    sum += pixelHistogram[i];
  }
  return sum;
}

void printPixelHistogram(unsigned int pixelHistogram[16]) {
  unsigned int allPixels = sumPixels(pixelHistogram);

  for (int i = 0; i < 16; i++) {
    printf("\t%d-%d: %.2f%%\n", i * 16, i * 16 + 15,
           (float)pixelHistogram[i] / allPixels * 100);
  }
  printf("\n");
}

void printHistogram(struct Histogram *histogram) {
  printf("----- Histogram -----:\n");
  printf("Blue\n");
  printPixelHistogram(histogram->blue);
  printf("Green\n");
  printPixelHistogram(histogram->green);
  printf("Red\n");
  printPixelHistogram(histogram->red);
}
