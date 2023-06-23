#include "shellheader.h"

/**
 * get_environ - a function that returns the string array copy of our environ
 * @val: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *val)
{
	if (!val->environ || val->env_changed)
	{
		val->environ = list_to_strings(val->env);
		val->env_changed = 0;
	}

	return (val->environ);
}

/**
 * _unsetenv - a function that Remove an environment variable
 * @val: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *val, char *var)
{
	list_t *node = val->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			val->env_changed = delete_node_at_index(&(val->env), i);
			i = 0;
			node = val->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (val->env_changed);
}

/**
 * _setenv - a function that Initialize a new environment variable,
 *             or modify an existing one
 * @val: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *val, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = val->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			val->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(val->env), buf, 0);
	free(buf);
	val->env_changed = 1;
	return (0);
}

