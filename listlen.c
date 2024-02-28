#include "shell.h"

size_t mwasi_list_len(const list_t *lee_h)
{
	size_t mwasi_i = 0;

	while (lee_h)
	{
		lee_h = lee_h->next;
		mwasi_i++;
	}
	return (mwasi_i);
}

char **mwasi_list_to_strings(list_t *lee_head)
{
	list_t *lee_node = lee_head;
	size_t mwasi_i = mwasi_list_len(lee_head), mwasi_j;
	char **lee_strs;
	char *lee_str;

	if (!lee_head || !mwasi_i)
		return (NULL);
	lee_strs = malloc(sizeof(char *) * (mwasi_i + 1));
	if (!lee_strs)
		return (NULL);
	for (mwasi_i = 0; lee_node; lee_node = lee_node->next, mwasi_i++)
	{
		lee_str = malloc(_strlen(lee_node->str) + 1);
		if (!lee_str)
		{
			for (mwasi_j = 0; mwasi_j < mwasi_i; mwasi_j++)
				free(lee_strs[mwasi_j]);
			free(lee_strs);
			return (NULL);
		}

		lee_str = _strcpy(lee_str, lee_node->str);
		lee_strs[mwasi_i] = lee_str;
	}
	lee_strs[mwasi_i] = NULL;
	return (lee_strs);
}

size_t mwasi_print_list(const list_t *lee_h)
{
	size_t mwasi_i = 0;

	while (lee_h)
	{
		_puts(convert_number(lee_h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(lee_h->str ? lee_h->str : "(nil)");
		_puts("\n");
		lee_h = lee_h->next;
		mwasi_i++;
	}
	return (mwasi_i);
}

list_t *mwasi_node_starts_with(list_t *lee_node, char *mwasi_prefix, char lee_c)
{
	char *lee_p = NULL;

	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, mwasi_prefix);
		if (lee_p && ((lee_c == -1) || (*lee_p == lee_c)))
			return (lee_node);
		lee_node = lee_node->next;
	}
	return (NULL);
}

ssize_t mwasi_get_node_index(list_t *lee_head, list_t *lee_node)
{
	size_t mwasi_i = 0;

	while (lee_head)
	{
		if (lee_head == lee_node)
			return (mwasi_i);
		lee_head = lee_head->next;
		mwasi_i++;
	}
	return (-1);
}

