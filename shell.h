#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
char *readline(void);
char **tokenline(char *line);
void execute(char *, char **, char **);
char** dir_in_path(void);
char *findcmd(char *, char **);
int cmpbuiltin(char **);
int exitshell(char **);
int changedirectory(char **);
#endif
