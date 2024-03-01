#include "shell.h"

/**
 * mwasi_erratoi - Converts a string to an integer
 * @lee_s: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise, -1 on error
 */
int mwasi_erratoi(char *lee_s)
{
	int lee_i = 0;
	unsigned long int lee_result = 0;

	if (*lee_s == '+')
		lee_s++;
	for (lee_i = 0;  lee_s[lee_i] != '\0'; lee_i++)
	{
		if (lee_s[lee_i] >= '0' && lee_s[lee_i] <= '9')
		{
			lee_result *= 10;
			lee_result += (lee_s[lee_i] - '0');
			if (lee_result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (lee_result);
}

/**
 * mwasi_print_error - Prints an error message
 * @lee_info: The parameter & return info struct
 * @lee_estr: String containing specified error type
 * Return: Nothing
 */
void mwasi_print_error(info_t *lee_info, char *lee_estr)
{
	_eputs(lee_info->fname);
	_eputs(": ");
	print_d(lee_info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(lee_info->argv[0]);
	_eputs(": ");
	_eputs(lee_estr);
}

/**
 * mwasi_print_d - Prints a decimal (integer) number (base 10)
 * @lee_input: The input
 * @lee_fd: The filedescriptor to write to
 * Return: Number of characters printed
 */
int mwasi_print_d(int lee_input, int lee_fd)
{
	int (*__putchar)(char) = _putchar;
	int lee_i, lee_count = 0;
	unsigned int lee_abs, lee_current;

	if (lee_fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (lee_input < 0)
	{
		lee_abs = -lee_input;
		__putchar('-');
		lee_count++;
	}
	else
		lee_abs = lee_input;
	lee_current = lee_abs;
	for (lee_i = 1000000000; lee_i > 1; lee_i /= 10)
	{
		if (lee_abs / lee_i)
		{
			__putchar('0' + lee_current / lee_i);
			lee_count++;
		}
		lee_current %= lee_i;
	}
	__putchar('0' + lee_current);
	lee_count++;

	return (lee_count);
}

/**
 * mwasi_convert_number - Converter function, a clone of itoa
 * @lee_num: Number
 * @lee_base: Base
 * @lee_flags: Argument flags
 * Return: String
 */
char *mwasi_convert_number(long int lee_num, int lee_base, int lee_flags)
{
	static char *lee_array;
	static char lee_buffer[50];
	char lee_sign = 0;
	char *lee_ptr;
	unsigned long lee_n = lee_num;

	if (!(lee_flags & CONVERT_UNSIGNED) && lee_num < 0)
	{
		lee_n = -lee_num;
		lee_sign = '-';
	}
	lee_array = lee_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	lee_ptr = &lee_buffer[49];
	*lee_ptr = '\0';

	do {
		*--lee_ptr = lee_array[lee_n % lee_base];
		lee_n /= lee_base;
	} while (lee_n != 0);

	if (lee_sign)
		*--lee_ptr = lee_sign;
	return (lee_ptr);
}

/**
 * mwasi_remove_comments - Replaces first instance of '#' with '\0'
 * @lee_buf: Address of the string to modify
 * Return: Always 0
 */
void mwasi_remove_comments(char *lee_buf)
{
	int lee_i;

	for (lee_i = 0; lee_buf[lee_i] != '\0'; lee_i++)
		if (lee_buf[lee_i] == '#' && (!lee_i || lee_buf[lee_i - 1] == ' '))
		{
			lee_buf[lee_i] = '\0';
			break;
		}
}

