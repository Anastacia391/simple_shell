#include "shell.h"
/**
  * main - simple shell that accepts a single command
  * @ac: argument counter
  * @av: argument vector
  * @envp: local environment
  * Return: 0 Always on Success
  */
int main(int ac __attribute__((unused)), char **av, char **envp)
{
	int n = 1;
	size_t size = strlen(av[0]) + 30;
	char *buff;
	pid_t ppid;
	char *command;
	char **tokens;

	while (n)
	{
		n = isatty(STDIN_FILENO);
		write(1, "~$ ", 4);
		command = readline();
		ppid = fork();
		if (ppid == 0)
		{
			tokens = tokenline(command);
			if (!tokens)
			{
				buff = malloc(sizeof(char) * size);
				buff = strdup(av[0]);
				strcat(buff, ": No such file or directory\n");
				write(2, buff, size);
				free(buff);
				exit(EXIT_FAILURE);
			}
			if (execve(tokens[0], tokens, envp) == -1)
			{
				perror(av[0]);
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
	}
	return (0);
}
/**
  * readline - read input from user
  * Return: pointer to entered command
  */
char *readline(void)
{
	char *buff = NULL;
	size_t buffsize = 0;

	if (getline(&buff, &buffsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		perror("");
	}
	return (buff);
}
/**
  * tokenline - parse commands for execution
  * @line: string to tokenize
  * Return: a double pointer to the first pointer of string
  */
char **tokenline(char *line)
{
	char *delimiter = " \t\n";
	char *token;
	char **tokens = malloc(sizeof(char *) * 64);
	int i = 0;

	if (!tokens)
	{
		perror("malloc failure tokens\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delimiter);
	if (!token)
	{
		exit(0);
	}
	while (token)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delimiter);
		i++;
	}
	tokens[i] = NULL;
	if (i > 1)
	{
		return (NULL);
	}
	return (tokens);
}
