#ifndef HISTOGRAM_H
#define HISTOGRAM_H

struct Histogram {
  unsigned int red[16];
  unsigned int green[16];
  unsigned int blue[16];
};

void printHistogram(struct Histogram *histogram);

unsigned int sumPixels(unsigned int pixelHistogram[16]);

void printPixelHistogram(unsigned int pixelHistogram[16]);


#endif
