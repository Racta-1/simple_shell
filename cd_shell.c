#include "shellheader.h"

/**
 * _myexit - a function that exits the shell
 * @var: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if var.argv[0] != "exit"
 */
int _myexit(info_t *var)
{
	int check;

	if (var->argv[1]) /* If there is an exit arguement */
	{
		check = _erratoi(var->argv[1]);
		if (check == -1)
		{
			var->status = 2;
			print_error(var, "Illegal number: ");
			_eputs(var->argv[1]);
			_eputchar('\n');
			return (1);
		}
		var->err_num = _erratoi(var->argv[1]);
		return (-2);
	}
	var->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that changes the current directory of the process
 * @var: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *var)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!var->argv[1])
	{
		dir = _getenv(var, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(var, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(var->argv[1], "-") == 0)
	{
		if (!_getenv(var, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(var, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(var, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(var->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(var, "can't cd to ");
		_eputs(var->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(var, "OLDPWD", _getenv(var, "PWD="));
		_setenv(var, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - a function that changes the current directory of the process
 * @var: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *var)
{
	char **arg_array;

	arg_array = var->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

