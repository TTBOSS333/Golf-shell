#ifndef SUSHI_H
#define SUSHI_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

#define SUSHI_MAX_INPUT 40 /* really modest :) */
#define SUSHI_HISTORY_LENGTH 32
#define SUSHI_DEFAULT_PROMPT "> "

char *sushi_read_line(FILE *in);
int sushi_read_config(char *fname, int ok_if_missing);

void sushi_store(char *line);
void sushi_show_history();
char *sushi_unquote(const char *line);
int sushi_parse_command(char *command);

extern int sushi_exit;
#endif
