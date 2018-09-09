#include <string.h>
#include <ctype.h>
#include "shout.h"
#include "say.h"

void shout(const char word[]) {
  int len = strlen(word);
  char buf[len];
  strcpy(buf, word);

  for (int i = 0; i < len; i++) {
    buf[i] = toupper(buf[i]);
  }

  say(buf);
}
