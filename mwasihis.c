#include "shell.h"

char *mwasi_get_history_file(info_t *lee_info)
{
	char *lee_buf, *mwasi_dir;

	mwasi_dir = _getenv(lee_info, "HOME=");
	if (!mwasi_dir)
		return (NULL);
	lee_buf = malloc(sizeof(char) * (_strlen(mwasi_dir) + _strlen(HIST_FILE) + 2));
	if (!lee_buf)
		return (NULL);
	lee_buf[0] = 0;
	_strcpy(lee_buf, mwasi_dir);
	_strcat(lee_buf, "/");
	_strcat(lee_buf, HIST_FILE);
	return (lee_buf);
}

int mwasi_write_history(info_t *lee_info)
{
	ssize_t lee_fd;
	char *lee_filename = mwasi_get_history_file(lee_info);
	list_t *lee_node = NULL;

	if (!lee_filename)
		return (-1);

	lee_fd = open(lee_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(lee_filename);
	if (lee_fd == -1)
		return (-1);
	for (lee_node = lee_info->history; lee_node; lee_node = lee_node->next)
	{
		_putsfd(lee_node->str, lee_fd);
		_putfd('\n', lee_fd);
	}
	_putfd(BUF_FLUSH, lee_fd);
	close(lee_fd);
	return (1);
}

int mwasi_read_history(info_t *lee_info)
{
	int lee_i, lee_last = 0, lee_linecount = 0;
	ssize_t lee_fd, lee_rdlen, lee_fsize = 0;
	struct stat lee_st;
	char *lee_buf = NULL, *lee_filename = mwasi_get_history_file(lee_info);

	if (!lee_filename)
		return (0);

	lee_fd = open(lee_filename, O_RDONLY);
	free(lee_filename);
	if (lee_fd == -1)
		return (0);
	if (!fstat(lee_fd, &lee_st))
		lee_fsize = lee_st.st_size;
	if (lee_fsize < 2)
		return (0);
	lee_buf = malloc(sizeof(char) * (lee_fsize + 1));
	if (!lee_buf)
		return (0);
	lee_rdlen = read(lee_fd, lee_buf, lee_fsize);
	lee_buf[lee_fsize] = 0;
	if (lee_rdlen <= 0)
		return (free(lee_buf), 0);
	close(lee_fd);
	for (lee_i = 0; lee_i < lee_fsize; lee_i++)
		if (lee_buf[lee_i] == '\n')
		{
			lee_buf[lee_i] = 0;
			mwasi_build_history_list(lee_info, lee_buf + lee_last, lee_linecount++);
			lee_last = lee_i + 1;
		}
	if (lee_last != lee_i)
		mwasi_build_history_list(lee_info, lee_buf + lee_last, lee_linecount++);
	free(lee_buf);
	lee_info->histcount = lee_linecount;
	while (lee_info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(lee_info->history), 0);
	mwasi_renumber_history(lee_info);
	return (lee_info->histcount);
}

int mwasi_build_history_list(info_t *lee_info, char *lee_buf, int lee_linecount)
{
	list_t *lee_node = NULL;

	if (lee_info->history)
		lee_node = lee_info->history;
	add_node_end(&lee_node, lee_buf, lee_linecount);

	if (!lee_info->history)
		lee_info->history = lee_node;
	return (0);
}

int mwasi_renumber_history(info_t *lee_info)
{
	list_t *lee_node = lee_info->history;
	int lee_i = 0;

	while (lee_node)
	{
		lee_node->num = lee_i++;
		lee_node = lee_node->next;
	}
	return (lee_info->histcount = lee_i);
}

