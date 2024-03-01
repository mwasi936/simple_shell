#include "shell.h"

/**
 * mwasi_get_environ - Returns the string array copy of our environ
 * @lee_info: Structure containing potential arguments
 * Return: String array copy of environ
 */
char **mwasi_get_environ(info_t *lee_info)
{
	if (!lee_info->environ || lee_info->env_changed)
	{
		lee_info->environ = list_to_strings(lee_info->env);
		lee_info->env_changed = 0;
	}

	return (lee_info->environ);
}

/**
 * mwasi_unsetenv - Remove an environment variable
 * @lee_info: Structure containing potential arguments
 * @lee_var: The string env var property
 * Return: 1 on delete, 0 otherwise
 */
int mwasi_unsetenv(info_t *lee_info, char *lee_var)
{
	list_t *lee_node = lee_info->env;
	size_t lee_i = 0;
	char *lee_p;

	if (!lee_node || !lee_var)
		return (0);

	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, lee_var);
		if (lee_p && *lee_p == '=')
		{
			lee_info->env_changed = delete_node_at_index(&(lee_info->env), lee_i);
			lee_i = 0;
			lee_node = lee_info->env;
			continue;
		}
		lee_node = lee_node->next;
		lee_i++;
	}
	return (lee_info->env_changed);
}

/**
 * mwasi_setenv - Initialize a new environment variable, or modify an existing one
 * @lee_info: Structure containing potential arguments
 * @lee_var: The string env var property
 * @lee_value: The string env var value
 * Return: Always 0
 */
int mwasi_setenv(info_t *lee_info, char *lee_var, char *lee_value)
{
	char *lee_buf = NULL;
	list_t *lee_node;
	char *lee_p;

	if (!lee_var || !lee_value)
		return (0);

	lee_buf = malloc(_strlen(lee_var) + _strlen(lee_value) + 2);
	if (!lee_buf)
		return (1);
	_strcpy(lee_buf, lee_var);
	_strcat(lee_buf, "=");
	_strcat(lee_buf, lee_value);
	lee_node = lee_info->env;
	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, lee_var);
		if (lee_p && *lee_p == '=')
		{
			free(lee_node->str);
			lee_node->str = lee_buf;
			lee_info->env_changed = 1;
			return (0);
		}
		lee_node = lee_node->next;
	}
	add_node_end(&(lee_info->env), lee_buf, 0);
	free(lee_buf);
	lee_info->env_changed = 1;
	return (0);
}
