CC=g++
CFLAGS=-O3 -Wall -pedantic -ansi -fopenmp
LDFLAGS= -fopenmp -ldl
EXECUTABLE=fract

DEPS = 
OBJ = Fract.o params.o jpge.o tga.o fractal.o

%.o: %.cc $(DEPS)
	$(CC) -c $< $(CFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	rm -f *.o

