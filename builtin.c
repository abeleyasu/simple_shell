#include "shell.h"

/* Example of a built-in command */
int my_exit(char **args)
{
    (void)args;
    return 0;  /* Indicate to exit the shell */
}
