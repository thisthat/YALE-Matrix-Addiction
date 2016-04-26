FLAG_C11 = -std=c++11 -stdlib=libc++
CC = g++
FLAGS = -O3 $(FLAG_C11)
NAME = YSFMMoltiplication
all: compile clean

compile: Main.o YSMF.o
	$(CC) YSMF.o  Main.o -o $(NAME) $(FLAGS)

YSMF.o: YSMF.cpp YSMF.hpp
	$(CC) $(FLAGS) -c $<

Main.o: Main.cpp Main.hpp
	$(CC) $(FLAGS) -c $<

Mul.o: Mul.cpp Mul.hpp
	$(CC) $(FLAGS) -c $<

clean:
	#rm *.o

demo: compile
	./$(NAME)
