#include "shell.h"

/**
 * mwasi_hsh - Main shell loop
 * @lee_info: The parameter & return info struct
 * @lee_av: The argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int mwasi_hsh(info_t *lee_info, char **lee_av)
{
	ssize_t lee_r = 0;
	int lee_builtin_ret = 0;

	while (lee_r != -1 && lee_builtin_ret != -2)
	{
		clear_info(lee_info);
		if (interactive(lee_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		lee_r = get_input(lee_info);
		if (lee_r != -1)
		{
			set_info(lee_info, lee_av);
			lee_builtin_ret = find_builtin(lee_info);
			if (lee_builtin_ret == -1)
				find_cmd(lee_info);
		}
		else if (interactive(lee_info))
			_putchar('\n');
		free_info(lee_info, 0);
	}
	write_history(lee_info);
	free_info(lee_info, 1);
	if (!interactive(lee_info) && lee_info->status)
		exit(lee_info->status);
	if (lee_builtin_ret == -2)
	{
		if (lee_info->err_num == -1)
			exit(lee_info->status);
		exit(lee_info->err_num);
	}
	return (lee_builtin_ret);
}

/**
 * mwasi_find_builtin - Finds a builtin command
 * @lee_info: The parameter & return info struct
 * Return: -1 if builtin not found, 0 if successful, 1 if not successful, -2 if exit()
 */
int mwasi_find_builtin(info_t *lee_info)
{
	int lee_i, lee_builtin_ret = -1;
	builtin_table lee_builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (lee_i = 0; lee_builtintbl[lee_i].type; lee_i++)
		if (_strcmp(lee_info->argv[0], lee_builtintbl[lee_i].type) == 0)
		{
			lee_info->line_count++;
			lee_builtin_ret = lee_builtintbl[lee_i].func(lee_info);
			break;
		}
	return (lee_builtin_ret);
}

/**
 * mwasi_find_cmd - Finds a command in PATH
 * @lee_info: The parameter & return info struct
 * Return: void
 */
void mwasi_find_cmd(info_t *lee_info)
{
	char *lee_path = NULL;
	int lee_i, lee_k;

	lee_info->path = lee_info->argv[0];
	if (lee_info->linecount_flag == 1)
	{
		lee_info->line_count++;
		lee_info->linecount_flag = 0;
	}
	for (lee_i = 0, lee_k = 0; lee_info->arg[lee_i]; lee_i++)
		if (!is_delim(lee_info->arg[lee_i], " \t\n"))
			lee_k++;
	if (!lee_k)
		return;

	lee_path = find_path(lee_info, _getenv(lee_info, "PATH="), lee_info->argv[0]);
	if (lee_path)
	{
		lee_info->path = lee_path;
		fork_cmd(lee_info);
	}
	else
	{
		if ((interactive(lee_info) || _getenv(lee_info, "PATH=")
			|| lee_info->argv[0][0] == '/') && is_cmd(lee_info, lee_info->argv[0]))
			fork_cmd(lee_info);
		else if (*(lee_info->arg) != '\n')
		{
			lee_info->status = 127;
			print_error(lee_info, "not found\n");
		}
	}
}

/**
 * mwasi_fork_cmd - Forks an exec thread to run cmd
 * @lee_info: The parameter & return info struct
 * Return: void
 */
void mwasi_fork_cmd(info_t *lee_info)
{
	pid_t lee_child_pid;

	lee_child_pid = fork();
	if (lee_child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (lee_child_pid == 0)
	{
		if (execve(lee_info->path, lee_info->argv, get_environ(lee_info)) == -1)
		{
			free_info(lee_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(lee_info->status));
		if (WIFEXITED(lee_info->status))
		{
			lee_info->status = WEXITSTATUS(lee_info->status);
			if (lee_info->status == 126)
				print_error(lee_info, "Permission denied\n");
		}
	}
}
