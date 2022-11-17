#include "s21_grep_lib.h"

int main(int argc, char *argv[]) {
  // int index = 0;
  // int flagForFirst = 1;
  opt Options = {0};
  parcer(argc, argv, &Options);
  char *pattern = argv[optind];
  while (optind < argc) {
    reader(Options, pattern, argv[optind]);
    optind++;
  }
}