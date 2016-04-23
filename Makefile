FLAG_C11 = -std=c++11 -stdlib=libc++
CC = g++
FLAGS = -O3 $(FLAG_C11)
NAME = YSFMMoltiplication
all: compile clean

compile: Main.cpp Main.hpp
	$(CC) $(FLAGS) Main.cpp -o $(NAME)

clean: 
	#rm *.o

demo: compile
	./$(NAME)