#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function prototypes */
void prompt(void);
char **parse_input(char *line);
void execute(char **args);

#endif /* SHELL_H */
