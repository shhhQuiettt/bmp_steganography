gcc -c bmp_utils/bmp_header_utils.c -o build/bmp_header_utils.o 
gcc -c stegano.c -o build/stegano.o
gcc build/stegano.o build/bmp_header_utils.o -Wextra -Wall -o bin/stegano
# valgrind --leak-check=full --show-leak-kinds=all ./stegano
