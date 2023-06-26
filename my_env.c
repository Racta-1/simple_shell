#include "shellheader.h"

/**
 * _myenv - a function that prints the current environment
 * @var: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *var)
{
	print_list_str(var->env);
	return (0);
}

/**
 * _getenv - a function that gets the value of an environ variable
 * @var: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *var, const char *name)
{
	list_t *node = var->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that Initialize a new environment variable,
 *             or modify an existing one
 * @var: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *var)
{
	if (var->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(var, var->argv[1], var->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function that Remove an environment variable
 * @var: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *var)
{
	int i;

	if (var->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= var->argc; i++)
		_unsetenv(var, var->argv[i]);

	return (0);
}

/**
 * populate_env_list - a function that populates env linked list
 * @var: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *var)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	var->env = node;
	return (0);
}
