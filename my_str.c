#include "shell.h"

/**
 * mwasi_strncpy - Copies a string
 * @lee_dest: The destination string to be copied to
 * @lee_src: The source string
 * @lee_n: The amount of characters to be copied
 * Return: The destination string
 */
char *mwasi_strncpy(char *lee_dest, char *lee_src, int lee_n)
{
	int lee_i, lee_j;
	char *lee_s = lee_dest;

	lee_i = 0;
	while (lee_src[lee_i] != '\0' && lee_i < lee_n - 1)
	{
		lee_dest[lee_i] = lee_src[lee_i];
		lee_i++;
	}
	if (lee_i < lee_n)
	{
		lee_j = lee_i;
		while (lee_j < lee_n)
		{
			lee_dest[lee_j] = '\0';
			lee_j++;
		}
	}
	return (lee_s);
}

/**
 * mwasi_strncat - Concatenates two strings
 * @lee_dest: The first string
 * @lee_src: The second string
 * @lee_n: The amount of bytes to be maximally used
 * Return: The concatenated string
 */
char *mwasi_strncat(char *lee_dest, char *lee_src, int lee_n)
{
	int lee_i, lee_j;
	char *lee_s = lee_dest;

	lee_i = 0;
	lee_j = 0;
	while (lee_dest[lee_i] != '\0')
		lee_i++;
	while (lee_src[lee_j] != '\0' && lee_j < lee_n)
	{
		lee_dest[lee_i] = lee_src[lee_j];
		lee_i++;
		lee_j++;
	}
	if (lee_j < lee_n)
		lee_dest[lee_i] = '\0';
	return (lee_s);
}

/**
 * mwasi_strchr - Locates a character in a string
 * @lee_s: The string to be parsed
 * @lee_c: The character to look for
 * Return: A pointer to the first occurrence of the character c in the string s
 */
char *mwasi_strchr(char *lee_s, char lee_c)
{
	do {
		if (*lee_s == lee_c)
			return (lee_s);
	} while (*lee_s++ != '\0');

	return (NULL);
}

