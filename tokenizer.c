#include "shell.h"

/**
 * mwasi_strtow - Splits a string into words, ignoring repeat delimiters
 * @lee_str: The input string
 * @lee_d: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **mwasi_strtow(char *lee_str, char *lee_d)
{
	int lee_i, lee_j, lee_k, lee_m, lee_numwords = 0;
	char **lee_s;

	if (lee_str == NULL || lee_str[0] == 0)
		return (NULL);
	if (!lee_d)
		lee_d = " ";
	for (lee_i = 0; lee_str[lee_i] != '\0'; lee_i++)
		if (!is_delim(lee_str[lee_i], lee_d) && (is_delim(lee_str[lee_i + 1], lee_d) || !lee_str[lee_i + 1]))
			lee_numwords++;

	if (lee_numwords == 0)
		return (NULL);
	lee_s = malloc((1 + lee_numwords) * sizeof(char *));
	if (!lee_s)
		return (NULL);
	for (lee_i = 0, lee_j = 0; lee_j < lee_numwords; lee_j++)
	{
		while (is_delim(lee_str[lee_i], lee_d))
			lee_i++;
		lee_k = 0;
		while (!is_delim(lee_str[lee_i + lee_k], lee_d) && lee_str[lee_i + lee_k])
			lee_k++;
		lee_s[lee_j] = malloc((lee_k + 1) * sizeof(char));
		if (!lee_s[lee_j])
		{
			for (lee_k = 0; lee_k < lee_j; lee_k++)
				free(lee_s[lee_k]);
			free(lee_s);
			return (NULL);
		}
		for (lee_m = 0; lee_m < lee_k; lee_m++)
			lee_s[lee_j][lee_m] = lee_str[lee_i++];
		lee_s[lee_j][lee_m] = 0;
	}
	lee_s[lee_j] = NULL;
	return (lee_s);
}

/**
 * mwasi_strtow2 - Splits a string into words
 * @lee_str: The input string
 * @lee_d: The delimiter
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **mwasi_strtow2(char *lee_str, char lee_d)
{
	int lee_i, lee_j, lee_k, lee_m, lee_numwords = 0;
	char **lee_s;

	if (lee_str == NULL || lee_str[0] == 0)
		return (NULL);
	for (lee_i = 0; lee_str[lee_i] != '\0'; lee_i++)
		if ((lee_str[lee_i] != lee_d && lee_str[lee_i + 1] == lee_d) ||
		    (lee_str[lee_i] != lee_d && !lee_str[lee_i + 1]) || lee_str[lee_i + 1] == lee_d)
			lee_numwords++;
	if (lee_numwords == 0)
		return (NULL);
	lee_s = malloc((1 + lee_numwords) * sizeof(char *));
	if (!lee_s)
		return (NULL);
	for (lee_i = 0, lee_j = 0; lee_j < lee_numwords; lee_j++)
	{
		while (lee_str[lee_i] == lee_d && lee_str[lee_i] != lee_d)
			lee_i++;
		lee_k = 0;
		while (lee_str[lee_i + lee_k] != lee_d && lee_str[lee_i + lee_k] && lee_str[lee_i + lee_k] != lee_d)
			lee_k++;
		lee_s[lee_j] = malloc((lee_k + 1) * sizeof(char));
		if (!lee_s[lee_j])
		{
			for (lee_k = 0; lee_k < lee_j; lee_k++)
				free(lee_s[lee_k]);
			free(lee_s);
			return (NULL);
		}
		for (lee_m = 0; lee_m < lee_k; lee_m++)
			lee_s[lee_j][lee_m] = lee_str[lee_i++];
		lee_s[lee_j][lee_m] = 0;
	}
	lee_s[lee_j] = NULL;
	return (lee_s);
}

