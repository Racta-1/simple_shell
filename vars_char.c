#include "shellheader.h"

/**
 * is_chain - a function that test if current char in buffer is a chain delimeter
 * @var: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *var, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		var->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		var->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		var->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - a function that checks we should continue chaining based on last status
 * @var: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *var, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (var->cmd_buf_type == CMD_AND)
	{
		if (var->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (var->cmd_buf_type == CMD_OR)
	{
		if (!var->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - a function that replaces an aliases in the tokenized string
 * @var: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *var)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(var->alias, var->argv[0], '=');
		if (!node)
			return (0);
		free(var->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		var->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - a function that replaces vars in the tokenized string
 * @var: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *var)
{
	int i = 0;
	list_t *node;

	for (i = 0; var->argv[i]; i++)
	{
		if (var->argv[i][0] != '$' || !var->argv[i][1])
			continue;

		if (!_strcmp(var->argv[i], "$?"))
		{
			replace_string(&(var->argv[i]),
					_strdup(convert_number(var->status, 10, 0)));
			continue;
		}
		if (!_strcmp(var->argv[i], "$$"))
		{
			replace_string(&(var->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(var->env, &var->argv[i][1], '=');
		if (node)
		{
			replace_string(&(var->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&var->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a function that replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

