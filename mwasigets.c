#include "shell.h"

/**
 * mwasi_clear_info - Initializes info_t struct
 * @lee_info: Struct address
 */
void mwasi_clear_info(info_t *lee_info)
{
	lee_info->arg = NULL;
	lee_info->argv = NULL;
	lee_info->path = NULL;
	lee_info->argc = 0;
}

/**
 * mwasi_set_info - Initializes info_t struct
 * @lee_info: Struct address
 * @lee_av: Argument vector
 */
void mwasi_set_info(info_t *lee_info, char **lee_av)
{
	int lee_i = 0;

	lee_info->fname = lee_av[0];
	if (lee_info->arg)
	{
		lee_info->argv = strtow(lee_info->arg, " \t");
		if (!lee_info->argv)
		{
			lee_info->argv = malloc(sizeof(char *) * 2);
			if (lee_info->argv)
			{
				lee_info->argv[0] = _strdup(lee_info->arg);
				lee_info->argv[1] = NULL;
			}
		}
		for (lee_i = 0; lee_info->argv && lee_info->argv[lee_i]; lee_i++)
			;
		lee_info->argc = lee_i;

		replace_alias(lee_info);
		replace_vars(lee_info);
	}
}

/**
 * mwasi_free_info - Frees info_t struct fields
 * @lee_info: Struct address
 * @lee_all: True if freeing all fields
 */
void mwasi_free_info(info_t *lee_info, int lee_all)
{
	ffree(lee_info->argv);
	lee_info->argv = NULL;
	lee_info->path = NULL;
	if (lee_all)
	{
		if (!lee_info->cmd_buf)
			free(lee_info->arg);
		if (lee_info->env)
			free_list(&(lee_info->env));
		if (lee_info->history)
			free_list(&(lee_info->history));
		if (lee_info->alias)
			free_list(&(lee_info->alias));
		ffree(lee_info->environ);
		lee_info->environ = NULL;
		bfree((void **)lee_info->cmd_buf);
		if (lee_info->readfd > 2)
			close(lee_info->readfd);
		_putchar(BUF_FLUSH);
	}
}
