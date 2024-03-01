#include "shell.h"

/**
 * mwasi_strlen - Returns the length of a string
 * @lee_s: The string whose length to check
 * Return: Integer length of string
 */
int mwasi_strlen(char *lee_s)
{
	int lee_i = 0;

	if (!lee_s)
		return (0);

	while (*lee_s++)
		lee_i++;
	return (lee_i);
}

/**
 * mwasi_strcmp - Performs lexicographic comparison of two strings
 * @lee_s1: The first string
 * @lee_s2: The second string
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int mwasi_strcmp(char *lee_s1, char *lee_s2)
{
	while (*lee_s1 && *lee_s2)
	{
		if (*lee_s1 != *lee_s2)
			return (*lee_s1 - *lee_s2);
		lee_s1++;
		lee_s2++;
	}
	if (*lee_s1 == *lee_s2)
		return (0);
	else
		return (*lee_s1 < *lee_s2 ? -1 : 1);
}

/**
 * mwasi_starts_with - Checks if needle starts with haystack
 * @lee_haystack: String to search
 * @lee_needle: The substring to find
 * Return: Address of next char of haystack or NULL
 */
char *mwasi_starts_with(const char *lee_haystack, const char *lee_needle)
{
	while (*lee_needle)
		if (*lee_needle++ != *lee_haystack++)
			return (NULL);
	return ((char *)lee_haystack);
}

/**
 * mwasi_strcat - Concatenates two strings
 * @lee_dest: The destination buffer
 * @lee_src: The source buffer
 * Return: Pointer to destination buffer
 */
char *mwasi_strcat(char *lee_dest, char *lee_src)
{
	char *lee_ret = lee_dest;

	while (*lee_dest)
		lee_dest++;
	while (*lee_src)
		*lee_dest++ = *lee_src++;
	*lee_dest = *lee_src;
	return (lee_ret);
}
