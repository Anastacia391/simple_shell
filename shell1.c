#include "shell.h"
/**
  * main - simple shell that accepts a single command
  * @ac: argument counter
  * @av: argument vector
  * Return: 0 Always on Success
  */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
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
				printf("%s: ", av[0]);
				perror("");
				exit(EXIT_FAILURE);
			}
			if (execve(tokens[0], tokens, NULL) == -1)
			{
				printf("%s: Command not found: %s\n", av[0], tokens[0]);
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
