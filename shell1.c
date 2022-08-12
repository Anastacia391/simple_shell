#include "shell.h"
/**
  * main - simple shell that accepts a single command
  * @ac: argument counter
  * @av: argument vector
  * @envp: local environment
  * Return: 0 Always on Success
  */
int main(int ac, char **av, char **envp)
{
	int n = 1;
	pid_t ppid;
	char *command;
	char **tokens;

	while (n)
	{
		n = isatty(STDIN_FILENO);
		printf("~$ ");
		command = readline();
		ppid = fork();
		if (ppid == 0)
		{
			tokens = tokenline(command);
			if (tokens == NULL)
			{
				dprintf(STDERR_FILENO, "%s: No such file or directory\n", av[ac - 1]);
				exit(EXIT_FAILURE);
			}
			if (execve(tokens[0], tokens, envp) == -1)
			{
				dprintf(STDERR_FILENO, "%s: No such file or directory\n", av[ac - 1]);
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
		printf("getline failure\n");
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
		exit(EXIT_SUCCESS);
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
