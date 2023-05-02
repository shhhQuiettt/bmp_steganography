gcc -c bmp_utils/bmp_header_utils.c -o build/bmp_header_utils.o 
gcc -c bmp_utils/histogram.c -o build/histogram.o 
gcc -c gray_and_histogram.c -o build/gray_and_histogram.o
gcc build/gray_and_histogram.o build/bmp_header_utils.o build/histogram.o -Wextra -Wall -o ./bin/gray_and_histogram
# valgrind --leak-check=full --show-leak-kinds=all ./gray_and_histogram



