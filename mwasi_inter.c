#include "shell.h"

/**
 * mwasi_interactive - returns true if shell is interactive mode
 * @lee_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int mwasi_interactive(info_t *lee_info)
{
	return (isatty(STDIN_FILENO) && lee_info->readfd <= 2);
}

/**
 * mwasi_is_delim - checks if character is a delimiter
 * @lee_c: the char to check
 * @mwasi_delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int mwasi_is_delim(char lee_c, char *mwasi_delim)
{
	while (*mwasi_delim)
		if (*mwasi_delim++ == lee_c)
			return (1);
	return (0);
}

/**
 * mwasi_isalpha - checks for alphabetic character
[2;2R[>77;30604;0c]10;rgb:bfbf/bfbf/bfbf]11;rgb:0000/0000/0000 * @lee_c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int mwasi_isalpha(int lee_c)
{
	if ((lee_c >= 'a' && lee_c <= 'z') || (lee_c >= 'A' && lee_c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * mwasi_atoi - converts a string to an integer
 * @lee_s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int mwasi_atoi(char *lee_s)
{
	int mwasi_i, lee_sign = 1, mwasi_flag = 0, lee_output;
	unsigned int mwasi_result = 0;

	for (mwasi_i = 0;  lee_s[mwasi_i] != '\0' && mwasi_flag != 2; mwasi_i++)
	{
		if (lee_s[mwasi_i] == '-')
			lee_sign *= -1;

		if (lee_s[mwasi_i] >= '0' && lee_s[mwasi_i] <= '9')
		{
			mwasi_flag = 1;
			mwasi_result *= 10;
			mwasi_result += (lee_s[mwasi_i] - '0');
		}
		else if (mwasi_flag == 1)
			mwasi_flag = 2;
	}

	if (lee_sign == -1)
		lee_output = -mwasi_result;
	else
		lee_output = mwasi_result;

	return (lee_output);
}

