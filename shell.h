#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void shell_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);

#endif /* SHELL_H */
