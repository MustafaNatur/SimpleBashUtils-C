#include "s21_cat_lib.h"
int parser(int argc, char *argv[], opt *Options) {
  int flag = 1;
  int rez = 0;
  int optionIndex = 0;
  const struct option arr[] = {{"number", 0, NULL, 'n'},
                               {"number-nonblank", 0, NULL, 'b'},
                               {"squeeze-blank", 0, NULL, 's'},
                               {NULL, 0, NULL, 0}};

  while ((rez = getopt_long(argc, argv, "+vbenstET", arr, &optionIndex)) !=
         -1) {
    switch (rez) {
      case 'v': {
        Options->v = 1;
        break;
      };

      case 'b': {
        Options->b = 1;
        break;
      };

      case 'e': {
        Options->e = 1;
        Options->v = 1;
        break;
      };

      case 'n': {
        Options->n = 1;
        break;
      };

      case 's': {
        Options->s = 1;
        break;
      };

      case 't': {
        Options->t = 1;
        Options->v = 1;
        break;
      }

      case 'E': {
        Options->E = 1;
        Options->v = 0;
        break;
      };

      case 'T': {
        Options->T = 1;
        Options->v = 0;
        break;
      };

      case '?':
      default: {
        flag = rez;
        break;
      };
    }
  }
  return flag;
}

int reader(opt *Options, char **argv) {
  int flag = 1;
  FILE *f;
  char ch = '\n';
  char ch2;
  int strCount = 0;
  int counter = 1;
  if ((f = fopen(argv[optind], "r")) != NULL) {
    if (is_regular_file(argv[optind])) {
      while ((ch2 = fgetc(f)) != EOF) {
        if (Options->s && ch == '\n' && ch2 == '\n') {
          strCount++;
          if (strCount > 1) {
            continue;
          }
        }

        if ((Options->n && ch == '\n' && !Options->b) ||
            ((Options->b) && ch == '\n' && ch2 != '\n')) {
          printf("%6d\t", counter++);
        }

        if (Options->e == 1 && ch2 == '\n') {
          printf("$");
        }

        if (Options->t && ch2 == '\t') {
          printf("^");
          ch2 = 'I';
        }

        if (Options->v && !(ch2 >= 32 && ch2 < 127) && ch2 != '\n' &&
            ch2 != '\t') {
          if (ch2 == 127) {
            printf("^");
            ch2 -= 64;
          } else if (ch2 < 32 && ch2 >= 0) {
            printf("^");
            ch2 += 64;
          }
        }

        if (ch == '\n' && ch2 != '\n') {
          strCount = 0;
        }
        ch = ch2;
        printf("%c", ch2);
      }
      fclose(f);
    } else {
      flag = -2;
    }
  } else {
    flag = -1;
  }
  return flag;
}

int is_regular_file(char *filename) {
  struct stat file_stat;
  stat(filename, &file_stat);
  return S_ISREG(file_stat.st_mode);
}
