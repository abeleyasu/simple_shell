#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *buffer;
    ssize_t chars_read;
    size_t buffer_size = BUFFER_SIZE;

    buffer = malloc(buffer_size * sizeof(char));
    if (buffer == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("#cisfun$ ");
        chars_read = getline(&buffer, &buffer_size, stdin);
        if (chars_read == -1)
        {
            printf("\n");
            break;
        }

        buffer[chars_read - 1] = '\0'; /* Removing newline character */

        if (access(buffer, X_OK) == 0)
        {
            pid_t child_pid = fork();
            if (child_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (child_pid == 0)
            {
                char *args[2];
                args[0] = buffer;
                args[1] = NULL;
                if (execve(buffer, args, NULL) == -1)
                {
                    perror(buffer);
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            fprintf(stderr, "%s: No such file or directory\n", buffer);
        }
    }

    free(buffer);
    return (EXIT_SUCCESS);
}
