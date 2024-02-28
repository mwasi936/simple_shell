#include "shell.h"

char **mwasi_get_environ(info_t *lee_info)
{
	if (!lee_info->environ || lee_info->env_changed)
	{
		lee_info->environ = list_to_strings(lee_info->env);
		lee_info->env_changed = 0;
	}

	return (lee_info->environ);
}

int mwasi_unsetenv(info_t *lee_info, char *mwasi_var)
{
	list_t *lee_node = lee_info->env;
	size_t lee_i = 0;
	char *lee_p;

	if (!lee_node || !mwasi_var)
		return (0);

	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, mwasi_var);
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

int mwasi_setenv(info_t *lee_info, char *mwasi_var, char *lee_value)
{
	char *lee_buf = NULL;
	list_t *lee_node;
	char *lee_p;

	if (!mwasi_var || !lee_value)
		return (0);

	lee_buf = malloc(_strlen(mwasi_var) + _strlen(lee_value) + 2);
	if (!lee_buf)
		return (1);
	_strcpy(lee_buf, mwasi_var);
	_strcat(lee_buf, "=");
	_strcat(lee_buf, lee_value);
	lee_node = lee_info->env;
	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, mwasi_var);
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

