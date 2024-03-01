#include "shell.h"

/**
 * mwasi_add_node - Adds a node to the start of the list
 * @lee_head: Address of pointer to head node
 * @lee_str: Str field of node
 * @lee_num: Node index used by history
 * Return: Pointer to the new head of the list
 */
list_t *mwasi_add_node(list_t **lee_head, const char *lee_str, int lee_num)
{
	list_t *lee_new_head;

	if (!lee_head)
		return (NULL);
	lee_new_head = malloc(sizeof(list_t));
	if (!lee_new_head)
		return (NULL);
	_memset((void *)lee_new_head, 0, sizeof(list_t));
	lee_new_head->num = lee_num;
	if (lee_str)
	{
		lee_new_head->str = _strdup(lee_str);
		if (!lee_new_head->str)
		{
			free(lee_new_head);
			return (NULL);
		}
	}
	lee_new_head->next = *lee_head;
	*lee_head = lee_new_head;
	return (lee_new_head);
}

/**
 * mwasi_add_node_end - Adds a node to the end of the list
 * @lee_head: Address of pointer to head node
 * @lee_str: Str field of node
 * @lee_num: Node index used by history
 * Return: Pointer to the new node
 */
list_t *mwasi_add_node_end(list_t **lee_head, const char *lee_str, int lee_num)
{
	list_t *lee_new_node, *lee_node;

	if (!lee_head)
		return (NULL);

	lee_node = *lee_head;
	lee_new_node = malloc(sizeof(list_t));
	if (!lee_new_node)
		return (NULL);
	_memset((void *)lee_new_node, 0, sizeof(list_t));
	lee_new_node->num = lee_num;
	if (lee_str)
	{
		lee_new_node->str = _strdup(lee_str);
		if (!lee_new_node->str)
		{
			free(lee_new_node);
			return (NULL);
		}
	}
	if (lee_node)
	{
		while (lee_node->next)
			lee_node = lee_node->next;
		lee_node->next = lee_new_node;
	}
	else
		*lee_head = lee_new_node;
	return (lee_new_node);
}

/**
 * mwasi_print_list_str - Prints only the str element of a list_t linked list
 * @lee_h: Pointer to the first node
 * Return: Size of the list
 */
size_t mwasi_print_list_str(const list_t *lee_h)
{
	size_t lee_i = 0;

	while (lee_h)
	{
		_puts(lee_h->str ? lee_h->str : "(nil)");
		_puts("\n");
		lee_h = lee_h->next;
		lee_i++;
	}
	return (lee_i);
}

/**
 * mwasi_delete_node_at_index - Deletes a node at a given index
 * @lee_head: Address of pointer to the first node
 * @lee_index: Index of the node to delete
 * Return: 1 on success, 0 on failure
 */
int mwasi_delete_node_at_index(list_t **lee_head, unsigned int lee_index)
{
	list_t *lee_node, *lee_prev_node;
	unsigned int lee_i = 0;

	if (!lee_head || !*lee_head)
		return (0);

	if (!lee_index)
	{
		lee_node = *lee_head;
		*lee_head = (*lee_head)->next;
		free(lee_node->str);
		free(lee_node);
		return (1);
	}
	lee_node = *lee_head;
	while (lee_node)
	{
		if (lee_i == lee_index)
		{
			lee_prev_node->next = lee_node->next;
			free(lee_node->str);
			free(lee_node);
			return (1);
		}
		lee_i++;
		lee_prev_node = lee_node;
		lee_node = lee_node->next;
	}
	return (0);
}

/**
 * mwasi_free_list - Frees all nodes of a list
 * @lee_head_ptr: Address of pointer to the head node
 * Return: void
 */
void mwasi_free_list(list_t **lee_head_ptr)
{
	list_t *lee_node, *lee_next_node, *lee_head;

	if (!lee_head_ptr || !*lee_head_ptr)
		return;
	lee_head = *lee_head_ptr;
	lee_node = lee_head;
	while (lee_node)
	{
		lee_next_node = lee_node->next;
		free(lee_node->str);
		free(lee_node);
		lee_node = lee_next_node;
	}
	*lee_head_ptr = NULL;
}
