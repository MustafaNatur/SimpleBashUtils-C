CC=gcc
FLAGS=-Wall -Wextra -Werror
all: s21_grep style clean

rebuild: cleanAll s21_grep style clean



cleanAll: 
	rm -rf *.o
	rm -rf s21_grep

clean:
	rm -rf *.o

style:
	clang-format -i -style=Google *.c

s21_grep: s21_grep_lib.o s21_grep.o 
	$(CC) $(FLAGS) s21_grep_lib.o s21_grep.o -o s21_grep
	rm -rf *.o


s21_grep.o: s21_grep.c
	$(CC) $(FLAGS) -c s21_grep.c

s21_grep_lib.o: s21_grep_lib.c
	$(CC) $(FLAGS) -c s21_grep_lib.c -o s21_grep_lib.o

test: all
	sh unit_test.sh
