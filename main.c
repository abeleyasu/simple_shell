#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, or an error code on failure.
 */
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    /* Main shell loop */
    while (1)
    {
        prompt();
    }

    return (0);
}
