#include "toolbox.h"

int main_mv (int argc, char * argv[])
{
	if (argc != 3)
	{
		puts("Bad command use.");
		return -1;
	}

	int res = rename(argv[1], argv[2]);

  if (res == -1)
    {
      res = main_cp(argc, argv);

      if (!res){ /*if res is anything but 0, copy failed*/
        unlink(argv[1]);
      }
    }

  if (res){ /*res is still 0 (false) upon success*/
    puts("mv command failed");
    return -1;
  }
  
  return EXIT_SUCCESS;
}
