gcc -c bmp_header_utils.c -o bmp_header_utils.o 
gcc -c main.c -o main.o && gcc main.o bmp_header_utils.o -Wextra -Wall -o main && valgrind --leak-check=full ./main
