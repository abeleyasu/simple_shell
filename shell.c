#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

int main(void)
{
    char *input;
    size_t bufsize = 32;
    input = (char *)malloc(bufsize * sizeof(char));
    if (input == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1)
    {
        printf("%s", PROMPT);
        if (getline(&input, &bufsize, stdin) == -1)
        {
            printf("\n");
            break;
        }

        input[0] = input[0]; /* Do nothing to avoid warning for unused variable */

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if (execve(input, NULL, NULL) == -1)
            {
                perror("execve");
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL);
        }
    }
    free(input);
    return (0);
}
