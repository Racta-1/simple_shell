#include "shellheader.h"

/**
 * clear_info - a function that initializes info_t struct
 * @var: struct address
 */
void clear_info(info_t *var)
{
	var->arg = NULL;
	var->argv = NULL;
	var->path = NULL;
	var->argc = 0;
}

/**
 * set_info - a function that initializes info_t struct
 * @var: struct address
 * @av: argument vector
 */
void set_info(info_t *var, char **av)
{
	int i = 0;

	var->fname = av[0];
	if (var->arg)
	{
		var->argv = strtow(var->arg, " \t");
		if (!var->argv)
		{
			var->argv = malloc(sizeof(char *) * 2);
			if (var->argv)
			{
				var->argv[0] = _strdup(var->arg);
				var->argv[1] = NULL;
			}
		}
		for (i = 0; var->argv && var->argv[i]; i++)
			;
		var->argc = i;

		replace_alias(var);
		replace_vars(var);
	}
}

/**
 * free_info - a function that frees info_t struct fields
 * @var: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *var, int all)
{
	ffree(var->argv);
	var->argv = NULL;
	var->path = NULL;
	if (all)
	{
		if (!var->cmd_buf)
			free(var->arg);
		if (var->env)
			free_list(&(var->env));
		if (var->history)
			free_list(&(var->history));
		if (var->alias)
			free_list(&(var->alias));
		ffree(var->environ);
			var->environ = NULL;
		bfree((void **)var->cmd_buf);
		if (var->readfd > 2)
			close(var->readfd);
		_putchar(BUF_FLUSH);
	}
}

