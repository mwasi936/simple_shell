#include "shell.h"

/**
 * mwasi_myhistory - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_myhistory(info_t *lee_info)
{
	print_list(lee_info->history);
	return (0);
}

/**
 * mwasi_unset_alias - sets alias to string
 * @lee_info: parameter struct
 * @lee_str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int mwasi_unset_alias(info_t *lee_info, char *lee_str)
{
	char *lee_p, lee_c;
	int lee_ret;

	lee_p = _strchr(lee_str, '=');
	if (!lee_p)
		return (1);
	lee_c = *lee_p;
	*lee_p = 0;
	lee_ret = delete_node_at_index(&(lee_info->alias),
		get_node_index(lee_info->alias, node_starts_with(lee_info->alias, lee_str, -1)));
	*lee_p = lee_c;
	return (lee_ret);
}

/**
 * mwasi_set_alias - sets alias to string
 * @lee_info: parameter struct
 * @lee_str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int mwasi_set_alias(info_t *lee_info, char *lee_str)
{
	char *lee_p;

	lee_p = _strchr(lee_str, '=');
	if (!lee_p)
		return (1);
	if (!*++lee_p)
		return (mwasi_unset_alias(lee_info, lee_str));

	mwasi_unset_alias(lee_info, lee_str);
	return (add_node_end(&(lee_info->alias), lee_str, 0) == NULL);
}

/**
 * mwasi_print_alias - prints an alias string
 * @lee_node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int mwasi_print_alias(list_t *lee_node)
{
	char *lee_p = NULL, *lee_a = NULL;

	if (lee_node)
	{
		lee_p = _strchr(lee_node->str, '=');
		for (lee_a = lee_node->str; lee_a <= lee_p; lee_a++)
			_putchar(*lee_a);
		_putchar('\'');
		_puts(lee_p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mwasi_myalias - mimics the alias builtin (man alias)
 * @lee_info: Structure containing potential arguments
 * Return: Always 0
 */
int mwasi_myalias(info_t *lee_info)
{
	int lee_i = 0;
	char *lee_p = NULL;
	list_t *lee_node = NULL;

	if (lee_info->argc == 1)
	{
		lee_node = lee_info->alias;
		while (lee_node)
		{
			mwasi_print_alias(lee_node);
			lee_node = lee_node->next;
		}
		return (0);
	}
	for (lee_i = 1; lee_info->argv[lee_i]; lee_i++)
	{
		lee_p = _strchr(lee_info->argv[lee_i], '=');
		if (lee_p)
			mwasi_set_alias(lee_info, lee_info->argv[lee_i]);
		else
			mwasi_print_alias(node_starts_with(lee_info->alias, lee_info->argv[lee_i], '='));
	}

	return (0);
}

