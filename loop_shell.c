#include "shellheader.h"

/**
 * hsh - the main shell loop
 * @var: the parameter & return var struct
 * @vec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *var, char **vec)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(var);
		if (interactive(var))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(var);
		if (r != -1)
		{
			set_info(var, vec);
			builtin_ret = find_builtin(var);
			if (builtin_ret == -1)
				find_cmd(var);
		}
		else if (interactive(var))
			_putchar('\n');
		free_info(var, 0);
	}
	write_history(var);
	free_info(var, 1);
	if (!interactive(var) && var->status)
		exit(var->status);
	if (builtin_ret == -2)
	{
		if (var->err_num == -1)
			exit(var->status);
		exit(var->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @var: the parameter & return var struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *var)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(var->argv[0], builtintbl[i].type) == 0)
		{
			var->line_count++;
			built_in_ret = builtintbl[i].func(var);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @var: the parameter & return var struct
 *
 * Return: void
 */
void find_cmd(info_t *var)
{
	char *path = NULL;
	int i, k;

	var->path = var->argv[0];
	if (var->linecount_flag == 1)
	{
		var->line_count++;
		var->linecount_flag = 0;
	}
	for (i = 0, k = 0; var->arg[i]; i++)
		if (!is_delim(var->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(var, _getenv(var, "PATH="), var->argv[0]);
	if (path)
	{
		var->path = path;
		fork_cmd(var);
	}
	else
	{
		if ((interactive(var) || _getenv(var, "PATH=")
					|| var->argv[0][0] == '/') && is_cmd(var, var->argv[0]))
			fork_cmd(var);
		else if (*(var->arg) != '\n')
		{
			var->status = 127;
			print_error(var, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @var: the parameter & return var struct
 *
 * Return: void
 */
void fork_cmd(info_t *var)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(var->path, var->argv, get_environ(var)) == -1)
		{
			free_info(var, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(var->status));
		if (WIFEXITED(var->status))
		{
			var->status = WEXITSTATUS(var->status);
			if (var->status == 126)
				print_error(var, "Permission denied\n");
		}
	}
}

