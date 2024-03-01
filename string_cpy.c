#include "shell.h"

/**
 * mwasi_strcpy - Copies a string
 * @lee_dest: The destination
 * @lee_src: The source
 * Return: Pointer to destination
 */
char *mwasi_strcpy(char *lee_dest, char *lee_src)
{
	int lee_i = 0;

	if (lee_dest == lee_src || lee_src == 0)
		return (lee_dest);
	while (lee_src[lee_i])
	{
		lee_dest[lee_i] = lee_src[lee_i];
		lee_i++;
	}
	lee_dest[lee_i] = 0;
	return (lee_dest);
}

/**
 * mwasi_strdup - Duplicates a string
 * @lee_str: The string to duplicate
 * Return: Pointer to the duplicated string
 */
char *mwasi_strdup(const char *lee_str)
{
	int lee_length = 0;
	char *lee_ret;

	if (lee_str == NULL)
		return (NULL);
	while (*lee_str++)
		lee_length++;
	lee_ret = malloc(sizeof(char) * (lee_length + 1));
	if (!lee_ret)
		return (NULL);
	for (lee_length++; lee_length--;)
		lee_ret[lee_length] = *--lee_str;
	return (lee_ret);
}

/**
 * mwasi_puts - Prints an input string
 * @lee_str: The string to be printed
 * Return: Nothing
 */
void mwasi_puts(char *lee_str)
{
	int lee_i = 0;

	if (!lee_str)
		return;
	while (lee_str[lee_i] != '\0')
	{
		_putchar(lee_str[lee_i]);
		lee_i++;
	}
}

/**
 * mwasi_putchar - Writes the character c to stdout
 * @lee_c: The character to print
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int mwasi_putchar(char lee_c)
{
	static int lee_i;
	static char lee_buf[WRITE_BUF_SIZE];

	if (lee_c == BUF_FLUSH || lee_i >= WRITE_BUF_SIZE)
	{
		write(1, lee_buf, lee_i);
		lee_i = 0;
	}
	if (lee_c != BUF_FLUSH)
		lee_buf[lee_i++] = lee_c;
	return (1);
}

