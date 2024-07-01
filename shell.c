#include "shell.h"

/**
 * prompt - Displays the shell prompt and waits for user input.
 */
void prompt(void)
{
    char *line = NULL;
    size_t len = 0;
    char **args;
    
    printf("$ ");
    if (getline(&line, &len, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);  /* Exit on EOF */
        }
        else
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    args = parse_input(line);
    execute(args);

    free(line);
    free(args);
}

/**
 * parse_input - Parses the user input into an array of arguments.
 * @line: The input line from the user.
 *
 * Return: An array of arguments.
 */
char **parse_input(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;

        if (i >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens)
            {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[i] = NULL;
    return tokens;
}

/**
 * execute - Executes the given command.
 * @args: An array of arguments.
 */
void execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
    {
        return;  /* No command entered */
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("fork");
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
