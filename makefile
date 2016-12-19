CC = g++
OBJS = main.o scene.o bitmap.o color.o figure.o light.o ray.o sphere.o plane.o
FLAGS = -std=c++11
raytracer : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o raytracer
main.o : bitmap.h bitmap.cpp color.cpp color.h figure.cpp figure.h light.cpp light.h ray.h ray.cpp sphere.h sphere.cpp main.cpp scene.cpp scene.h plane.cpp plane.h
	$(CC) $(FLAGS) -c main.cpp
scene.o : bitmap.h bitmap.cpp color.cpp color.h figure.cpp figure.h light.cpp light.h ray.h ray.cpp sphere.h sphere.cpp main.cpp scene.cpp scene.h plane.cpp plane.h
	$(CC) $(FLAGS) -c scene.cpp
bitmap.o : bitmap.h bitmap.cpp color.cpp color.h
	$(CC) $(FLAGS) -c bitmap.cpp
color.o : color.h color.cpp
	$(CC) $(FLAGS) -c color.cpp
figure.o : figure.h figure.cpp color.h color.cpp ray.h ray.cpp
	$(CC) $(FLAGS) -c figure.cpp
light.o : light.h light.cpp figure.cpp figure.h ray.h ray.cpp color.h color.cpp sphere.h sphere.cpp plane.cpp plane.h
	$(CC) $(FLAGS) -c light.cpp
ray.o : ray.h ray.cpp
	$(CC) $(FLAGS) -c ray.cpp
sphere.o : sphere.h sphere.cpp figure.cpp figure.h ray.h ray.cpp color.h color.cpp
	$(CC) $(FLAGS) -c sphere.cpp
plane.o : plane.h plane.cpp figure.cpp figure.h ray.h ray.cpp color.h color.cpp
	$(CC) $(FLAGS) -c plane.cpp
clean :
	rm *.o *~ raytracer
