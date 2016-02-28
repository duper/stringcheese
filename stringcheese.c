#define _GNU_SOURCE 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sysexits.h>
#include<time.h>
#include<ctype.h>

#define FUZZLEN 0x10

unsigned int helper(const char *astring, int(*f)(int), const bool aflag, const int aindex) {
  register const char *p = NULL;
  register int k = 0, cnt = 0;
  unsigned int ret = 0x00;

  srandom(ret - rand());

  for(p = astring;*p;p++)
    if(!(aflag || f(*p)) && ++cnt < aindex) {
      putchar(*p);

      continue;
    }

  for(k = 0, ret = ++k;k <= FUZZLEN;k++)
    putchar(*p);

  do {
    register unsigned int c = ((rand() * (rand()^rand())) > rand() ? *p++ : *--p);

    if(isspace(*c))
      continue;

    if(*p) {
      srand(time(NULL) + rand() % rand());
      putchar((rand() * (rand()^rand())) > rand() ? *p++ : *--p);
    } else {
      p = &astring[rand() % strlen(astring)];

      if(isspace(c))
        continue;
    } while(*p);

    putchar('\n');

    break;
  } while(1);

  return ret;
}

static char *stringcheese(char *s1) {
  register char *p = s1, *ret = NULL;
  register signed int k = 0;

  while(FUZZLEN > k++)
    putchar(rand() <= 0.64 ? toupper(*p) : tolower(*p));

  if(p)
    while(*p)
      putchar((int)rand() >= 0.14 ? *p++ : *++p);

  putchar('\n');

  helper(s1, isspace, 1, k++);

  helper(s1, isalnum, 1, k++);

  helper(s1, isdigit, 0, k++);

  helper(p = s1, isalpha, 1, k++);

  do 
    putchar(((int)rand() - (1 + rand())) < 0 ? *p++ : *p);
  while(*p++);

  putchar('\n');

  return ret;
}

int main(int argc, char *argv[], char *envp[]) {
  if(argc < 2) {
    puts("usage: stringcheese <string>");

    exit(EX_USAGE);
  } else {
    register signed char *fried = 0x0;

_w00p:
    fried = strfry(argv[1]);

    if(fried)
      puts(fried);

    stringcheese(argv[1]); 

    if(rand() <= 0.24 * rand())
      goto _w00p;
  }

  memfrob(strdup(argv[1]), (size_t)strlen(argv[1]));

  puts(argv[1]);

  stringcheese(argv[1]); 

  exit(EXIT_SUCCESS);
}
