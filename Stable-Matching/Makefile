CC=g++
CFLAGS=-std=c++11
SOURCES= helpers/Student.cpp helpers/Teacher.cpp 


GaleShapley: GaleShapley.cpp helpers/Student.cpp helpers/Teacher.cpp helpers/Pool.h helpers/helpFunctions.h
	$(CC) -o $@ $< $(SOURCES) $(CFLAGS)

clean:
	rm GaleShapley