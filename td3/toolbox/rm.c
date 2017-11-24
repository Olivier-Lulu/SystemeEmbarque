#include "toolbox.h"

int main_rm (int argc, char* argv[])
{
  if (argc != 2) {
    puts("Bad command use");
    return -1;
  }

  return unlink(argv[1]);
}
