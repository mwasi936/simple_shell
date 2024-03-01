#include "shell.h"

/**
 * mwasi_memset - Fills memory with a constant byte
 * @lee_s: The pointer to the memory area
 * @lee_b: The byte to fill *s with
 * @lee_n: The amount of bytes to be filled
 * Return: A pointer to the memory area s
 */
char *mwasi_memset(char *lee_s, char lee_b, unsigned int lee_n)
{
	unsigned int lee_i;

	for (lee_i = 0; lee_i < lee_n; lee_i++)
		lee_s[lee_i] = lee_b;
	return (lee_s);
}

/**
 * mwasi_ffree - Frees a string of strings
 * @lee_pp: String of strings
 */
void mwasi_ffree(char **lee_pp)
{
	char **lee_a = lee_pp;

	if (!lee_pp)
		return;
	while (*lee_pp)
		free(*lee_pp++);
	free(lee_a);
}

/**
 * mwasi_realloc - Reallocates a block of memory
 * @lee_ptr: Pointer to previous malloc'ated block
 * @lee_old_size: Byte size of previous block
 * @lee_new_size: Byte size of new block
 * Return: Pointer to the old block
 */
void *mwasi_realloc(void *lee_ptr, unsigned int lee_old_size, unsigned int lee_new_size)
{
	char *lee_p;

	if (!lee_ptr)
		return (malloc(lee_new_size));
	if (!lee_new_size)
		return (free(lee_ptr), NULL);
	if (lee_new_size == lee_old_size)
		return (lee_ptr);

	lee_p = malloc(lee_new_size);
	if (!lee_p)
		return (NULL);

	lee_old_size = lee_old_size < lee_new_size ? lee_old_size : lee_new_size;
	while (lee_old_size--)
		lee_p[lee_old_size] = ((char *)lee_ptr)[lee_old_size];
	free(lee_ptr);
	return (lee_p);
}

