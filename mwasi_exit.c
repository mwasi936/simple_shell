#include "shell.h"

/**
 * mwasi_myexit - exits the shell
 * @lee_info: Structure containing potential arguments
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit"
 */
int mwasi_myexit(info_t *lee_info)
{
	int lee_exitcheck;

	if (lee_info->argv[1])  /* If there is an exit argument */
	{
		lee_exitcheck = _erratoi(lee_info->argv[1]);
		if (lee_exitcheck == -1)
		{
			lee_info->status = 2;
			print_error(lee_info, "Illegal number: ");
			_eputs(lee_info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		lee_info->err_num = _erratoi(lee_info->argv[1]);
		return (-2);
	}
	lee_info->err_num = -1;
	return (-2);
}

/**
 * mwasi_mycd - changes the current directory of the process
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_mycd(info_t *lee_info)
{
	char *lee_s, *lee_dir, lee_buffer[1024];
	int lee_chdir_ret;

	lee_s = getcwd(lee_buffer, 1024);
	if (!lee_s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!lee_info->argv[1])
	{
		lee_dir = _getenv(lee_info, "HOME=");
		if (!lee_dir)
			lee_chdir_ret = chdir((lee_dir = _getenv(lee_info, "PWD=")) ? lee_dir : "/");
		else
			lee_chdir_ret = chdir(lee_dir);
	}
	else if (_strcmp(lee_info->argv[1], "-") == 0)
	{
		if (!_getenv(lee_info, "OLDPWD="))
		{
			_puts(lee_s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(lee_info, "OLDPWD=")), _putchar('\n');
		lee_chdir_ret = chdir((lee_dir = _getenv(lee_info, "OLDPWD=")) ? lee_dir : "/");
	}
	else
		lee_chdir_ret = chdir(lee_info->argv[1]);
	if (lee_chdir_ret == -1)
	{
		print_error(lee_info, "can't cd to ");
		_eputs(lee_info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(lee_info, "OLDPWD", _getenv(lee_info, "PWD="));
		_setenv(lee_info, "PWD", getcwd(lee_buffer, 1024));
	}
	return (0);
}

/**
 * mwasi_myhelp - changes the current directory of the process
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_myhelp(info_t *lee_info)
{
	char **lee_arg_array;

	lee_arg_array = lee_info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*lee_arg_array); /* temp att_unused workaround */
	return (0);
}
