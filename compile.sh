gcc -c bmp_header_utils.c -o bmp_header_utils.o 
gcc -c histogram.c -o histogram.o 
gcc -c gray_and_histogram.c -o gray_and_histogram.o
gcc gray_and_histogram.o bmp_header_utils.o histogram.o -Wextra -Wall -o gray_and_histogram
valgrind --leak-check=full --show-leak-kinds=all ./gray_and_histogram



