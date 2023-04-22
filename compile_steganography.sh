gcc -c bmp_header_utils.c -o bmp_header_utils.o 
gcc -c steganography.c -o steganography.o
gcc steganography.o bmp_header_utils.o -Wextra -Wall -o stegano
valgrind --leak-check=full --show-leak-kinds=all ./stegano
