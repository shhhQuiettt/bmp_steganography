#include "bmp_header_utils.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

FILE *open_file(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) {
    fprintf(stderr, "Error opening file %s", filename);
    exit(1);
  }
  return fp;
}

uint8_t *encode_char(uint8_t buffer[8], char c) {
  uint8_t *encoded_buffer = malloc(sizeof(uint8_t) * 8);

  for (int i = 0; i < 8; i++) {
    encoded_buffer[i] = buffer[i] & 0xFE;
    encoded_buffer[i] |= (c >> i) & 0x01;
  }
  return encoded_buffer;
}

char decode_char(uint8_t buffer[8]) {
  char c = 0;
  for (int i = 0; i < 8; i++) {
    c |= (buffer[i] & 0x01) << i;
  }
  return c;
}

int main(int argc, char **argv) {
  char *in_filename = "out.bmp";
  char *out_filename = NULL; //"out.bmp";
  char *message = "abcd";

  short encoding_mode = out_filename != NULL ? 1 : 0;

  // Asking user about decoding
  {
    printf("Do you want to decode the message? ([y]/n): ");
    char response;
    scanf("%c", &response);
    if (response == 'n') {
      return 0;
    }
  }

  FILE *in_fp = open_file(in_filename, "rb");

  BITMAPFILEHEADER *header = read_bmp_header(in_fp);
  BITMAPINFOHEADER *info_header = read_bmp_info_header(in_fp);

  print_bmp_header(header);
  print_bmp_info_header(info_header);

  if (encoding_mode) {
    uint8_t message_length = strlen(message);
    printf("message length: %d\n", message_length);

    FILE *out_fp = open_file(out_filename, "wb");

    uint8_t char_buffer[8];
    uint8_t *encoded_char_buffer = NULL;

    write_bmp_header(out_fp, header);
    write_bmp_info_header(out_fp, info_header);

    // Encoding message length
    fread(char_buffer, sizeof(uint8_t), 8, in_fp);
    encoded_char_buffer = encode_char(char_buffer, message_length);
    fwrite(encoded_char_buffer, sizeof(uint8_t), 8, out_fp);
    free(encoded_char_buffer);

    int char_index = 0;
    while (char_index < message_length &&
           fread(char_buffer, sizeof(uint8_t), 8, in_fp) == 8) {
      encoded_char_buffer = encode_char(char_buffer, message[char_index]);
      fwrite(encoded_char_buffer, sizeof(uint8_t), 8, out_fp);
      free(encoded_char_buffer);
      char_index++;
    }

    // Copying the rest of the file
    uint8_t buf = 0;
    while (fread(&buf, sizeof(uint8_t), 1, in_fp) > 0) {
      fwrite(&buf, sizeof(uint8_t), 1, out_fp);
    }
    fclose(out_fp);

  } else {
    // ask user if decode

    uint8_t encoded_char_buffer[8];

    fread(encoded_char_buffer, sizeof(uint8_t), 8, in_fp);
    uint8_t message_length = decode_char(encoded_char_buffer);

    char *message = malloc(sizeof(char) * message_length + 1);

    int char_index = 0;
    while (fread(encoded_char_buffer, sizeof(uint8_t), 8, in_fp) == 8 &&
           char_index < message_length) {
      message[char_index] = decode_char(encoded_char_buffer);
      char_index++;
    }
    message[message_length] = '\0';

    printf("Message: %s\n", message);
    free(message);
  }

  free(header);
  free(info_header);
  fclose(in_fp);
}
