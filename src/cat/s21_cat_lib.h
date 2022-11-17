#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
} opt;

int parser(int argc, char *argv[], opt *Options);
int reader(opt *Options, char **argv);
void Opt_n(FILE *f);
void Opt_b(FILE *f);
int is_regular_file(char *filename);
