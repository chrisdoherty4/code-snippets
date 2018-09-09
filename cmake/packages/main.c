#include <string.h>
#include <stdio.h>
#include "say.h"
#include "shout.h"

int main() {
  char *sentence = "Hello world!";

  say(sentence);

  shout(sentence);

  return 0;
}
