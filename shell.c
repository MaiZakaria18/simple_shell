#include "shell.h"
/**
 * main - Main function for the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @environ: Environment variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv, char **environ)
{
	char command[MAX_COMMAND_LENGTH];
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	(void)argc;
	(void)argv;

	if (!isatty(STDIN_FILENO))
	{
		while ((nread = _getline(&line, &len, stdin)) > 0)
		{
			if (nread != 0)
			{ _strcpy(command, line);
				handle_command(command, environ); }
			free_memory((void **)&line);
			line = NULL;
			if (nread != -1)
			{ line = malloc(MAX_COMMAND_LENGTH);
				len = MAX_COMMAND_LENGTH; }
		}
	}
	else
	{ signal(SIGINT, handle_sigint);
		_print(SHELL_PROMPT);
		fflush(stdout);
		while ((nread = _getline(&line, &len, stdin)) != -1)
		{ _strcpy(command, line);
			handle_command(command, environ);
			_print(SHELL_PROMPT);
			fflush(stdout);
			free_memory((void **)&line);
			line = NULL;
			if (nread != -1)
			{ line = malloc(MAX_COMMAND_LENGTH);
				len = MAX_COMMAND_LENGTH; }
		}
	}
	free_memory((void **)&line);
	return (0);
}
