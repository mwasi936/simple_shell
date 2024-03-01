#include "shell.h"

/**
 * mwasi_is_cmd - Determines if a file is an executable command
 * @lee_info: The info struct
 * @lee_path: Path to the file
 * Return: 1 if true, 0 otherwise
 */
int mwasi_is_cmd(info_t *lee_info, char *lee_path)
{
	struct stat lee_st;

	(void)lee_info;
	if (!lee_path || stat(lee_path, &lee_st))
		return (0);

	if (lee_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * mwasi_dup_chars - Duplicates characters
 * @lee_pathstr: The PATH string
 * @lee_start: Starting index
 * @lee_stop: Stopping index
 * Return: Pointer to new buffer
 */
char *mwasi_dup_chars(char *lee_pathstr, int lee_start, int lee_stop)
{
	static char lee_buf[1024];
	int lee_i = 0, lee_k = 0;

	for (lee_k = 0, lee_i = lee_start; lee_i < lee_stop; lee_i++)
		if (lee_pathstr[lee_i] != ':')
			lee_buf[lee_k++] = lee_pathstr[lee_i];
	lee_buf[lee_k] = 0;
	return (lee_buf);
}

/**
 * mwasi_find_path - Finds this cmd in the PATH string
 * @lee_info: The info struct
 * @lee_pathstr: The PATH string
 * @lee_cmd: The cmd to find
 * Return: Full path of cmd if found or NULL
 */
char *mwasi_find_path(info_t *lee_info, char *lee_pathstr, char *lee_cmd)
{
	int lee_i = 0, lee_curr_pos = 0;
	char *lee_path;

	if (!lee_pathstr)
		return (NULL);
	if ((_strlen(lee_cmd) > 2) && starts_with(lee_cmd, "./"))
	{
		if (mwasi_is_cmd(lee_info, lee_cmd))
			return (lee_cmd);
	}
	while (1)
	{
		if (!lee_pathstr[lee_i] || lee_pathstr[lee_i] == ':')
		{
			lee_path = mwasi_dup_chars(lee_pathstr, lee_curr_pos, lee_i);
			if (!*lee_path)
				_strcat(lee_path, lee_cmd);
			else
			{
				_strcat(lee_path, "/");
				_strcat(lee_path, lee_cmd);
			}
			if (mwasi_is_cmd(lee_info, lee_path))
				return (lee_path);
			if (!lee_pathstr[lee_i])
				break;
			lee_curr_pos = lee_i;
		}
		lee_i++;
	}
	return (NULL);
}

