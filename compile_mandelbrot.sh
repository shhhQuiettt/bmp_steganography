
gcc -c bmp_utils/bmp_header_utils.c -o build/bmp_header_utils.o 
gcc -c mandelbrot.c -o build/mandelbrot.o
gcc build/mandelbrot.o build/bmp_header_utils.o -Wextra -Wall -o bin/mandelbrot -lm
./bin/mandelbrot 1000 1000 mandelbrot.bmp
# valgrind --leak-check=full --show-leak-kinds=all ./bin/mandelbrot 1000 1000 mandelbrot.bmp