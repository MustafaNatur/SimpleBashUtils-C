#include "s21_cat_lib.h"
int main(int argc, char *argv[]) {
  opt Options = {0};

  if (parser(argc, argv, &Options) == 1) {
    while (optind < argc) {
      int res = reader(&Options, argv);
      if (res == -1) {
        fprintf(stderr, "cat: %s: No such file or directory", argv[optind]);
      }

      if (res == -2) {
        fprintf(stderr, "cat: %s: Is a directory", argv[optind]);
      }
      optind++;
    }
  }
}
