#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int e;  // поиск файла по шаблону
  int i;  // посик по слову игнорируя регистр
  int v;  // ищет все строки кроме заданой
  int c;  // выводит количество совпадений
  int l;  // выводит только название файла с совпадением
  int n;  // выводит номер строчки где был найдено совпадение

  int h;  // подавляет вывод название файла где был найдено вхождение
  int s;  // не выводит предупреждение о несуществующем или о нечитаемом файле
  int f;  // берет шаблоны из файла
  int o;  // выводит сам шаблон при совпадении
  int noOpt;
  int notOneFile;
} opt;

int parcer(int argc, char **argv, opt *Options);
int reader(opt Options, char *pattern, char *file);
