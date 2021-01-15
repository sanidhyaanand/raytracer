BIN = bin/raytracer.exe

SRCS = main.cpp 

INCLUDES = utility/vec3.h utility/color.h utility/ray.h

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(SRCS) -o $(BIN)

test:
	bin/raytracer.exe > image.ppm

clean:
	rm -f *~ *.o $(BIN)