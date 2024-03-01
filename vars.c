#include "shell.h"

/**
 * mwasi_is_chain - Test if current char in buffer is a chain delimiter
 * @lee_info: The parameter struct
 * @lee_buf: The char buffer
 * @lee_p: Address of current position in buf
 * Return: 1 if chain delimiter, 0 otherwise
 */
int mwasi_is_chain(info_t *lee_info, char *lee_buf, size_t *lee_p)
{
	size_t lee_j = *lee_p;

	if (lee_buf[lee_j] == '|' && lee_buf[lee_j + 1] == '|')
	{
		lee_buf[lee_j] = 0;
		lee_j++;
		lee_info->cmd_buf_type = CMD_OR;
	}
	else if (lee_buf[lee_j] == '&' && lee_buf[lee_j + 1] == '&')
	{
		lee_buf[lee_j] = 0;
		lee_j++;
		lee_info->cmd_buf_type = CMD_AND;
	}
	else if (lee_buf[lee_j] == ';') /* found end of this command */
	{
		lee_buf[lee_j] = 0; /* replace semicolon with null */
		lee_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*lee_p = lee_j;
	return (1);
}

/**
 * mwasi_check_chain - Checks if we should continue chaining based on last status
 * @lee_info: The parameter struct
 * @lee_buf: The char buffer
 * @lee_p: Address of current position in buf
 * @lee_i: Starting position in buf
 * @lee_len: Length of buf
 * Return: Void
 */
void mwasi_check_chain(info_t *lee_info, char *lee_buf, size_t *lee_p, size_t lee_i, size_t lee_len)
{
	size_t lee_j = *lee_p;

	if (lee_info->cmd_buf_type == CMD_AND)
	{
		if (lee_info->status)
		{
			lee_buf[lee_i] = 0;
			lee_j = lee_len;
		}
	}
	if (lee_info->cmd_buf_type == CMD_OR)
	{
		if (!lee_info->status)
		{
			lee_buf[lee_i] = 0;
			lee_j = lee_len;
		}
	}

	*lee_p = lee_j;
}

/**
 * mwasi_replace_alias - Replaces aliases in the tokenized string
 * @lee_info: The parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int mwasi_replace_alias(info_t *lee_info)
{
	int lee_i;
	list_t *lee_node;
	char *lee_p;

	for (lee_i = 0; lee_i < 10; lee_i++)
	{
		lee_node = node_starts_with(lee_info->alias, lee_info->argv[0], '=');
		if (!lee_node)
			return (0);
		free(lee_info->argv[0]);
		lee_p = _strchr(lee_node->str, '=');
		if (!lee_p)
			return (0);
		lee_p = _strdup(lee_p + 1);
		if (!lee_p)
			return (0);
		lee_info->argv[0] = lee_p;
	}
	return (1);
}

/**
 * mwasi_replace_vars - Replaces vars in the tokenized string
 * @lee_info: The parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int mwasi_replace_vars(info_t *lee_info)
{
	int lee_i = 0;
	list_t *lee_node;

	for (lee_i = 0; lee_info->argv[lee_i]; lee_i++)
	{
		if (lee_info->argv[lee_i][0] != '$' || !lee_info->argv[lee_i][1])
			continue;

		if (!_strcmp(lee_info->argv[lee_i], "$?"))
		{
			replace_string(&(lee_info->argv[lee_i]),
				_strdup(convert_number(lee_info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(lee_info->argv[lee_i], "$$"))
		{
			replace_string(&(lee_info->argv[lee_i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		lee_node = node_starts_with(lee_info->env, &lee_info->argv[lee_i][1], '=');
		if (lee_node)
		{
			replace_string(&(lee_info->argv[lee_i]),
				_strdup(_strchr(lee_node->str, '=') + 1));
			continue;
		}
		replace_string(&lee_info->argv[lee_i], _strdup(""));

	}
	return (0);
}

/**
 * mwasi_replace_string - Replaces string
 * @lee_old: Address of old string
 * @lee_new: New string
 * Return: 1 if replaced, 0 otherwise
 */
int mwasi_replace_string(char **lee_old, char *lee_new)
{
	free(*lee_old);
	*lee_old = lee_new;
	return (1);
}

