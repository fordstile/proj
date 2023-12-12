#include "shell.h"

/**
 * set_info - initializes info_t struct
 * @infos: struct address
 * @avg: argument vector
 */
void set_info(info_t *infos, char **avg)
{
	int index = 0;
	infos->fname = avg[0];

	if (infos->arg)
	{
		infos->argv = strtow(infos->arg, " \t");

		if (!infos->argv)
		{
			infos->argv = malloc(sizeof(char *) * 2);

			if (infos->argv)
			{
				infos->argv[0] = _strdup(infos->arg);
				infos->argv[1] = NULL;
			}
		}

		for (index = 0; infos->argv && infos->argv[index]; index++)
			infos->argc = index;

		replace_alias(infos);
		replace_vars(infos);
	}
}

/**
 * free_info - frees info_t struct
 * @infos: struct address
 * @alls: if freeing all fields true
 */
void free_info(info_t *infos, int alls)
{
	ffree(infos->argv);
	infos->argv = NULL;
	infos->path = NULL;

	if (alls)
	{
		if (!infos->cmd_buf)
			free(infos->arg);

		if (infos->env)
			free_list(&(infos->env));

		if (infos->history)
			free_list(&(infos->history));

		if (infos->alias)
			free_list(&(infos->alias));

		ffree(infos->environ);
		infos->environ = NULL;
		bfree((void **)infos->cmd_buf);

		if (infos->readfd > 2)
			close(infos->readfd);

		_putchar(BUF_FLUSH);
	}
}

/**
 * clear_info - initializes info_t struct
 * @infos: struct address
 */
void clear_info(info_t *infos)
{
	infos->arg = NULL;
	infos->argv = NULL;
	infos->path = NULL;
	infos->argc = 0;
}

