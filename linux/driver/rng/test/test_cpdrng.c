#include <stdio.h>

int main(int argc, char *argv[])
{
  unsigned short buf[128] = {0};
  int ret = 0, i;
  FILE *fh = fopen("/dev/cpdrng", "r");

  if (fh == NULL) {
    fprintf(stderr, "Failed to open device file\n");
    return 1;
  }

  ret = fread(buf, 2, 128, fh);

  if (ret < 0) {
    fprintf(stderr, "Failed to read random bytes\n");
  }

  for (i = 0; i < 128; i+=4) {
    printf("Buf [%3d]: %04x %04x %04x %04x\n", i, buf[i], buf[i+1], buf[i+2], buf[i+3]);
  }

  return 0;
}
