#include "shell.h"

/**
 * mwasi_input_buf - Buffers chained commands
 * @lee_info: Parameter struct
 * @lee_buf: Address of buffer
 * @lee_len: Address of len var
 * Return: Bytes read
 */
ssize_t mwasi_input_buf(info_t *lee_info, char **lee_buf, size_t *lee_len)
{
	ssize_t lee_r = 0;
	size_t lee_len_p = 0;

	if (!*lee_len) /* if nothing left in the buffer, fill it */
	{
		free(*lee_buf);
		*lee_buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		lee_r = getline(lee_buf, &lee_len_p, stdin);
#else
		lee_r = _getline(lee_info, lee_buf, &lee_len_p);
#endif
		if (lee_r > 0)
		{
			if ((*lee_buf)[lee_r - 1] == '\n')
			{
				(*lee_buf)[lee_r - 1] = '\0'; /* remove trailing newline */
				lee_r--;
			}
			lee_info->linecount_flag = 1;
			remove_comments(*lee_buf);
			build_history_list(lee_info, *lee_buf, lee_info->histcount++);
			{
				*lee_len = lee_r;
				lee_info->cmd_buf = lee_buf;
			}
		}
	}
	return (lee_r);
}

/**
 * mwasi_get_input - Gets a line minus the newline
 * @lee_info: Parameter struct
 * Return: Bytes read
 */
ssize_t mwasi_get_input(info_t *lee_info)
{
	static char *lee_buf;
	static size_t lee_i, lee_j, lee_len;
	ssize_t lee_r = 0;
	char **lee_buf_p = &(lee_info->arg), *lee_p;

	_putchar(BUF_FLUSH);
	lee_r = mwasi_input_buf(lee_info, &lee_buf, &lee_len);
	if (lee_r == -1) /* EOF */
		return (-1);
	if (lee_len)	/* we have commands left in the chain buffer */
	{
		lee_j = lee_i; /* init new iterator to current buf position */
		lee_p = lee_buf + lee_i; /* get pointer for return */

		check_chain(lee_info, lee_buf, &lee_j, lee_i, lee_len);
		while (lee_j < lee_len) /* iterate to semicolon or end */
		{
			if (is_chain(lee_info, lee_buf, &lee_j))
				break;
			lee_j++;
		}

		lee_i = lee_j + 1; /* increment past nulled ';'' */
		if (lee_i >= lee_len) /* reached end of buffer? */
		{
			lee_i = lee_len = 0; /* reset position and length */
			lee_info->cmd_buf_type = CMD_NORM;
		}

		*lee_buf_p = lee_p; /* pass back pointer to current command position */
		return (_strlen(lee_p)); /* return length of current command */
	}

	*lee_buf_p = lee_buf; /* else not a chain, pass back buffer from _getline() */
	return (lee_r); /* return length of buffer from _getline() */
}

/**
 * mwasi_read_buf - Reads a buffer
 * @lee_info: Parameter struct
 * @lee_buf: Buffer
 * @lee_i: Size
 * Return: Number of bytes read
 */
ssize_t mwasi_read_buf(info_t *lee_info, char *lee_buf, size_t *lee_i)
{
	ssize_t lee_r = 0;

	if (*lee_i)
		return (0);
	lee_r = read(lee_info->readfd, lee_buf, READ_BUF_SIZE);
	if (lee_r >= 0)
		*lee_i = lee_r;
	return (lee_r);
}

/**
 * mwasi_getline - Gets the next line of input from STDIN
 * @lee_info: Parameter struct
 * @lee_ptr: Address of pointer to buffer, preallocated or NULL
 * @lee_length: Size of preallocated ptr buffer if not NULL
 * Return: Number of bytes read
 */
int mwasi_getline(info_t *lee_info, char **lee_ptr, size_t *lee_length)
{
	static char lee_buf[READ_BUF_SIZE];
	static size_t lee_i, lee_len;
	size_t lee_k;
	ssize_t lee_r = 0, lee_s = 0;
	char *lee_p = NULL, *lee_new_p = NULL, *lee_c;

	lee_p = *lee_ptr;
	if (lee_p && lee_length)
		lee_s = *lee_length;
	if (lee_i == lee_len)
		lee_i = lee_len = 0;

	lee_r = mwasi_read_buf(lee_info, lee_buf, &lee_len);
	if (lee_r == -1 || (lee_r == 0 && lee_len == 0))
		return (-1);

	lee_c = _strchr(lee_buf + lee_i, '\n');
	lee_k = lee_c ? 1 + (unsigned int)(lee_c - lee_buf) : lee_len;
	lee_new_p = _realloc(lee_p, lee_s, lee_s ? lee_s + lee_k : lee_k + 1);
	if (!lee_new_p) /* MALLOC FAILURE! */
		return (lee_p ? free(lee_p), -1 : -1);

	if (lee_s)
		_strncat(lee_new_p, lee_buf + lee_i, lee_k - lee_i);
	else
		_strncpy(lee_new_p, lee_buf + lee_i, lee_k - lee_i + 1);

	lee_s += lee_k - lee_i;
	lee_i = lee_k;
	lee_p = lee_new_p;

	if (lee_length)
		*lee_length = lee_s;
	*lee_ptr = lee_p;
	return (lee_s);
}

/**
 * mwasi_sigintHandler - Blocks ctrl-C
 * @lee_sig_num: The signal number
 * Return: void
 */
void mwasi_sigintHandler(__attribute__((unused))int lee_sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
