CC=g++
CFLAGS=-std=c++11
SOURCES= Student.cpp Teacher.cpp 


GaleShapley: GaleShapley.cpp Student.cpp Teacher.cpp Pool.h helpFunctions.h
	$(CC) -o $@ $< $(SOURCES) $(CFLAGS)

clean:
	rm GaleShapley