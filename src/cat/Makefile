CC=gcc
FLAGS=-Wall -Wextra -Werror
all: s21_cat style clean

cleanAll: 
	rm -rf *.o
	rm -rf s21_cat

clean:
	rm -rf *.o

style:
	clang-format -i -style=Google *.c

s21_cat: s21_cat_lib.o s21_cat.o 
	$(CC) $(FLAGS) s21_cat_lib.o s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c
	$(CC) $(FLAGS) -c s21_cat.c

s21_cat_lib.o: s21_cat_lib.c
	$(CC) $(FLAGS) -c s21_cat_lib.c -o s21_cat_lib.o

test: all 
	sh test_func_cat.sh


