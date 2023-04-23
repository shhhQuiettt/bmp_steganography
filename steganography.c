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
  char *in_filename = "c.bmp";
  char *out_filename = "out.bmp";
  char *message = "abcd";

  short encoding_mode = out_filename != NULL ? 1 : 0;

  int message_length = strlen(message);

  FILE *in_fp = open_file(in_filename, "rb");
  FILE *out_fp = encoding_mode ? open_file(out_filename, "wb") : NULL;

  BITMAPFILEHEADER *header = read_bmp_header(in_fp);
  BITMAPINFOHEADER *info_header = read_bmp_info_header(in_fp);

  write_bmp_header(out_fp, header);
  write_bmp_info_header(out_fp, info_header);

  print_bmp_header(header);
  print_bmp_info_header(info_header);


  if (encoding_mode) {
    uint8_t char_buffer[8];
    uint8_t *encoded_char_buffer = NULL;

    fread(char_buffer, sizeof(uint8_t), 8, in_fp);
    encoded_char_buffer = encode_char(char_buffer, message_length);
    fwrite(encoded_char_buffer, sizeof(uint8_t), 8, out_fp);
    free(encoded_char_buffer);

    /*   printf("char: %c  ", message[char_index]); */

    /*       printf("%d %d %d %d %d %d %d %d\n", char_buffer[0],
     * char_buffer[1], */
    /*              char_buffer[2], char_buffer[3], char_buffer[4],
     * char_buffer[5], */
    /*              char_buffer[6], char_buffer[7]); */
    /*       encoded_char_buffer = encode_char(char_buffer,
     * message[char_index]); */
    /*       printf("%d %d %d %d %d %d %d %d\n\n", char_buffer[0],
     * char_buffer[1], */
    /*              char_buffer[2], char_buffer[3], char_buffer[4],
     * char_buffer[5], */
    /*              char_buffer[6], char_buffer[7]); */

    /*   printf("%d %d %d %d %d %d %d %d\n", encoded_char_buffer[0],
     */
    /*          encoded_char_buffer[1], encoded_char_buffer[2], */
    /*          encoded_char_buffer[3], encoded_char_buffer[4], */
    /*          encoded_char_buffer[5], encoded_char_buffer[6], */
    /*          encoded_char_buffer[7]); */
    int char_index = 0;
    while (fread(char_buffer, sizeof(uint8_t), 8, in_fp) == 8 &&
           char_index < message_length) {
        printf("charo\n");
      fwrite(char_buffer, sizeof(uint8_t), 8, out_fp);
      char_index++;
    }
    /* //write the rest of the file */
    /* uint8_t buf; */
    while (fread(char_buffer, sizeof(uint8_t), 8, in_fp) > 0) {
        printf("writing rest of file\n");
      fwrite(char_buffer, sizeof(uint8_t), 8, out_fp);
    }

  } else {
    uint8_t encoded_char_buffer[8];

    fread(encoded_char_buffer, sizeof(uint8_t), 8, in_fp);
    int message_length = (int)decode_char(encoded_char_buffer);
    char *message = malloc(sizeof(char) * message_length + 1);

    int char_index = 0;
    while (fread(encoded_char_buffer, sizeof(uint8_t), 8, in_fp) == 8 &&
           char_index < message_length) {
      message[char_index] = decode_char(encoded_char_buffer);
      char_index++;
    }
    message[message_length] = '\0';
    printf("Message: %s\n", message);
  }

  free(header);
  free(info_header);
  fclose(in_fp);
  fclose(out_fp);
}
