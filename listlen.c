#include "shell.h"

/**
 * mwasi_list_len - Determines the length of a linked list
 * @lee_h: Pointer to the first node
 * Return: Size of the list
 */
size_t mwasi_list_len(const list_t *lee_h)
{
	size_t lee_i = 0;

	while (lee_h)
	{
		lee_h = lee_h->next;
		lee_i++;
	}
	return (lee_i);
}

/**
 * mwasi_list_to_strings - Returns an array of strings of the list->str
 * @lee_head: Pointer to the first node
 * Return: Array of strings
 */
char **mwasi_list_to_strings(list_t *lee_head)
{
	list_t *lee_node = lee_head;
	size_t lee_i = mwasi_list_len(lee_head), lee_j;
	char **lee_strs;
	char *lee_str;

	if (!lee_head || !lee_i)
		return (NULL);
	lee_strs = malloc(sizeof(char *) * (lee_i + 1));
	if (!lee_strs)
		return (NULL);
	for (lee_i = 0; lee_node; lee_node = lee_node->next, lee_i++)
	{
		lee_str = malloc(_strlen(lee_node->str) + 1);
		if (!lee_str)
		{
			for (lee_j = 0; lee_j < lee_i; lee_j++)
				free(lee_strs[lee_j]);
			free(lee_strs);
			return (NULL);
		}

		lee_str = _strcpy(lee_str, lee_node->str);
		lee_strs[lee_i] = lee_str;
	}
	lee_strs[lee_i] = NULL;
	return (lee_strs);
}

/**
 * mwasi_print_list - Prints all elements of a list_t linked list
 * @lee_h: Pointer to the first node
 * Return: Size of the list
 */
size_t mwasi_print_list(const list_t *lee_h)
{
	size_t lee_i = 0;

	while (lee_h)
	{
		_puts(convert_number(lee_h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(lee_h->str ? lee_h->str : "(nil)");
		_puts("\n");
		lee_h = lee_h->next;
		lee_i++;
	}
	return (lee_i);
}

/**
 * mwasi_node_starts_with - Returns node whose string starts with prefix
 * @lee_node: Pointer to list head
 * @lee_prefix: String to match
 * @lee_c: The next character after prefix to match
 * Return: Match node or null
 */
list_t *mwasi_node_starts_with(list_t *lee_node, char *lee_prefix, char lee_c)
{
	char *lee_p = NULL;

	while (lee_node)
	{
		lee_p = starts_with(lee_node->str, lee_prefix);
		if (lee_p && ((lee_c == -1) || (*lee_p == lee_c)))
			return (lee_node);
		lee_node = lee_node->next;
	}
	return (NULL);
}

/**
 * mwasi_get_node_index - Gets the index of a node
 * @lee_head: Pointer to list head
 * @lee_node: Pointer to the node
 * Return: Index of node or -1
 */
ssize_t mwasi_get_node_index(list_t *lee_head, list_t *lee_node)
{
	size_t lee_i = 0;

	while (lee_head)
	{
		if (lee_head == lee_node)
			return (lee_i);
		lee_head = lee_head->next;
		lee_i++;
	}
	return (-1);
}
