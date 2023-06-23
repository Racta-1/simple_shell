#include "shellheader.h"
/**
 * _myhistory - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @var: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *var)
{
	print_list(var->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @var: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *var, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(var->alias),
		get_node_index(var->alias, node_starts_with(var->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @var: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *var, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(var, str));

	unset_alias(var, str);
	return (add_node_end(&(var->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @var: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *var)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (var->argc == 1)
	{
		node = var->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; var->argv[i]; i++)
	{
		p = _strchr(var->argv[i], '=');
		if (p)
			set_alias(var, var->argv[i]);
		else
			print_alias(node_starts_with(var->alias, var->argv[i], '='));
	}

	return (0);
}
