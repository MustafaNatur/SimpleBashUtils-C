#include "s21_grep_lib.h"
static const char *optstr = "ef:ivclnhsfo";

int parcer(int argc, char **argv, opt *Options) {
  int flag = 1;
  int res;
  int needOpt = 1;
  int optionIndex = 0;
  const struct option arr[] = {{NULL, 0, NULL, 0}};
  while ((res = getopt_long(argc, argv, optstr, arr, &optionIndex)) != -1) {
    Options->e = 1;
    needOpt = 0;
    switch (res) {
      case 'i': {
        Options->i = 1;
        break;
      };

      case 'e': {
        Options->e = 1;
        Options->f = 0;
        break;
      };

      case 'h': {
        Options->h = 1;
        break;
      }

      case 'v': {
        Options->v = 1;
        break;
      }

      case 'c': {
        Options->c = 1;
        break;
      }

      case 'l': {
        Options->l = 1;
        break;
      }

      case 'n': {
        Options->n = 1;
        break;
      }

      case 'f': {
        Options->e = 0;
        Options->f = 1;
        break;
      }

      case 's': {
        Options->s = 1;
        opterr = 0;
        break;
      }

      case 'o': {
        Options->o = 1;
        break;
      }

      case '?': {
        flag = res;
        break;
      }
      default: {
        Options->noOpt = 1;
        break;
      }
    }
  }

  if (needOpt == 1) {
    Options->e = 1;
    Options->noOpt = 1;
  }

  if (optind + 2 < argc) {
    Options->notOneFile = 1;
  }
  return flag;
}

int reader(opt Options, char *pattern, char *file) {
  char str[9999];
  // char files[9999];
  int counter = 0;
  int counterString = 0;
  regex_t reegex;
  regcomp(&reegex, pattern, REG_EXTENDED);
  FILE *f;
  int resSearch;

  if ((f = fopen(file, "r")) != NULL) {
    while ((fgets(str, 9999, f)) != NULL) {
      counterString++;
      resSearch = regexec(&reegex, str, 0, NULL, 0);

      if (Options.i) {
        regfree(&reegex);
        regcomp(&reegex, pattern, REG_ICASE);
        resSearch = regexec(&reegex, str, 0, NULL, 0);
      }

      if (Options.v) {
        resSearch = !resSearch;
      }

      if (Options.h) {
        Options.notOneFile = 0;
      }

      if (resSearch == 0) {
        counter++;
        if (str[strlen(str) - 1] != '\n') {
          int end = strlen(str);
          str[end] = '\n';
          str[end + 1] = '\0';
        }

        if (Options.c != 1 && Options.l != 1) {
          if (Options.notOneFile && Options.n) {
            printf("%s:%d:%s", file, counterString, str);
          } else if (Options.notOneFile && !Options.n) {
            printf("%s:%s", file, str);
          } else if (!Options.notOneFile && Options.n) {
            printf("%d:%s", counterString, str);
          } else {
            printf("%s", str);
          }
        }
      }
    }

    if (Options.c && !Options.l) {
      if (Options.notOneFile) {
        printf("%s:%d\n", file, counter);
      } else {
        printf("%d\n", counter);
      }
    }

    if (Options.c && Options.l) {
      if (counter == 0) {
        counter = 0;
      } else {
        counter = 1;
      }
      if (Options.notOneFile) {
        printf("%s:%d\n", file, counter);
      } else {
        printf("%d\n", counter);
      }
    }

    if (Options.l && counter != 0) {
      counter = 1;
      printf("%s\n", file);
    }
    fclose(f);
  }

  regfree(&reegex);
  return 1;
}
