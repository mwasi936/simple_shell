#include "shell.h"

/**
 * mwasi_myenv - prints the current environment
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_myenv(info_t *lee_info)
{
	print_list_str(lee_info->env);
	return (0);
}

/**
 * mwasi_getenv - gets the value of an environ variable
 * @lee_info: Structure containing potential arguments
 * @lee_name: env var name
 * Return: the value
 */
char *mwasi_getenv(info_t *lee_info, const char *lee_name)
{
	list_t *lee_node = lee_info->env;
	char *lee_p;

	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, lee_name);
		if (lee_p && *lee_p)
			return (lee_p);
		lee_node = lee_node->next;
	}
	return (NULL);
}

/**
 * mwasi_mysetenv - Initialize a new environment variable,
 *                  or modify an existing one
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_mysetenv(info_t *lee_info)
{
	if (lee_info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(lee_info, lee_info->argv[1], lee_info->argv[2]))
		return (0);
	return (1);
}

/**
 * mwasi_myunsetenv - Remove an environment variable
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_myunsetenv(info_t *lee_info)
{
	int lee_i;

	if (lee_info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (lee_i = 1; lee_i <= lee_info->argc; lee_i++)
		_unsetenv(lee_info, lee_info->argv[lee_i]);

	return (0);
}

/**
 * mwasi_populate_env_list - populates env linked list
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_populate_env_list(info_t *lee_info)
{
	list_t *lee_node = NULL;
	size_t lee_i;

	for (lee_i = 0; environ[lee_i]; lee_i++)
		add_node_end(&lee_node, environ[lee_i], 0);
	lee_info->env = lee_node;
	return (0);
}

