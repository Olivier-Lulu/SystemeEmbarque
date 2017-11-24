#include "toolbox.h"

int main_rmdir (int argc, char* argv[])
{
  if (argc != 2) {
    puts("Bad command use");
    return -1;
  }

  return rmdir(argv[1]);
}
