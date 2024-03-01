#include "shell.h"

/**
 * mwasi_eputs - prints an input string
 * @lee_str: the string to be printed
 * Return: Nothing
 */
void mwasi_eputs(char *lee_str)
{
	int lee_i = 0;

	if (!lee_str)
		return;
	while (lee_str[lee_i] != '\0')
	{
		_eputchar(lee_str[lee_i]);
		lee_i++;
	}
}

/**
 * mwasi_eputchar - writes the character c to stderr
 * @lee_c: The character to print
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int mwasi_eputchar(char lee_c)
{
	static int lee_i;
	static char lee_buf[WRITE_BUF_SIZE];

	if (lee_c == BUF_FLUSH || lee_i >= WRITE_BUF_SIZE)
	{
		write(2, lee_buf, lee_i);
		lee_i = 0;
	}
	if (lee_c != BUF_FLUSH)
		lee_buf[lee_i++] = lee_c;
	return (1);
}

/**
 * mwasi_putfd - writes the character c to given fd
 * @lee_c: The character to print
 * @lee_fd: The filedescriptor to write to
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int mwasi_putfd(char lee_c, int lee_fd)
{
	static int lee_i;
	static char lee_buf[WRITE_BUF_SIZE];

	if (lee_c == BUF_FLUSH || lee_i >= WRITE_BUF_SIZE)
	{
		write(lee_fd, lee_buf, lee_i);
		lee_i = 0;
	}
	if (lee_c != BUF_FLUSH)
		lee_buf[lee_i++] = lee_c;
	return (1);
}

/**
 * mwasi_putsfd - prints an input string
 * @lee_str: the string to be printed
 * @lee_fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int mwasi_putsfd(char *lee_str, int lee_fd)
{
	int lee_i = 0;

	if (!lee_str)
		return (0);
	while (*lee_str)
	{
		lee_i += mwasi_putfd(*lee_str++, lee_fd);
	}
	return (lee_i);
}
