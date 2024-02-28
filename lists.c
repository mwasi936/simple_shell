#include "shell.h"

list_t *mwasi_add_node(list_t **lee_head, const char *lee_str, int mwasi_num)
{
	list_t *lee_new_head;

	if (!lee_head)
		return (NULL);
	lee_new_head = malloc(sizeof(list_t));
	if (!lee_new_head)
		return (NULL);
	_memset((void *)lee_new_head, 0, sizeof(list_t));
	lee_new_head->num = mwasi_num;
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

list_t *mwasi_add_node_end(list_t **lee_head, const char *lee_str, int mwasi_num)
{
	list_t *lee_new_node, *lee_node;

	if (!lee_head)
		return (NULL);

	lee_node = *lee_head;
	lee_new_node = malloc(sizeof(list_t));
	if (!lee_new_node)
		return (NULL);
	_memset((void *)lee_new_node, 0, sizeof(list_t));
	lee_new_node->num = mwasi_num;
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

size_t mwasi_print_list_str(const list_t *lee_h)
{
	size_t mwasi_i = 0;

	while (lee_h)
	{
		_puts(lee_h->str ? lee_h->str : "(nil)");
		_puts("\n");
		lee_h = lee_h->next;
		mwasi_i++;
	}
	return (mwasi_i);
}

int mwasi_delete_node_at_index(list_t **lee_head, unsigned int mwasi_index)
{
	list_t *lee_node, *lee_prev_node;
	unsigned int lee_i = 0;

	if (!lee_head || !*lee_head)
		return (0);

	if (!mwasi_index)
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
		if (lee_i == mwasi_index)
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

