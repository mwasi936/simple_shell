#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define CMD_CHAIN 0
#define CMD_AND 1
#define CMD_OR 2

typedef struct info_s {
	int status;
	int err_num;
	char *arg;
	char **argv;
	char *path;
	int argc;
	int line_count;
	int linecount_flag;
	int cmd_buf_type;
	char **cmd_buf;
	char **environ;
	int env_changed;
	struct list_s *env;
	struct list_s *history;
	struct list_s *alias;
	int readfd;
} info_t;

typedef struct list_s {
	char *str;
	int num;
	struct list_s *next;
} list_t;

typedef struct builtin_s {
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function prototypes */
char *mwasi_strcpy(char *lee_dest, char *lee_src);
char *mwasi_strdup(const char *lee_str);
void mwasi_puts(char *lee_str);
int mwasi_putchar(char lee_c);
char **mwasi_strtow(char *lee_str, char *lee_d);
char **mwasi_strtow2(char *lee_str, char lee_d);
int mwasi_is_chain(info_t *lee_info, char *lee_buf, size_t *lee_p);
void mwasi_check_chain(info_t *lee_info, char *lee_buf, size_t *lee_p, size_t lee_i, size_t lee_len);
int mwasi_replace_alias(info_t *lee_info);
int mwasi_replace_vars(info_t *lee_info);
int mwasi_replace_string(char **lee_old, char *lee_new);
int mwasi_hsh(info_t *lee_info, char **lee_av);
int mwasi_find_builtin(info_t *lee_info);
void mwasi_find_cmd(info_t *lee_info);
void mwasi_fork_cmd(info_t *lee_info);
char *mwasi_strcat(char *lee_dest, char *lee_src);
int mwasi_strlen(char *lee_s);
int mwasi_strcmp(char *lee_s1, char *lee_s2);
char *mwasi_starts_with(const char *lee_haystack, const char *lee_needle);
void execute_command(char *command);

#endif /* SHELL_H */
