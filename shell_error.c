#include "shellheader.h"
/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int val = 0;

	if (!str)
		return;
	while (str[val] != '\0')
	{
		_eputchar(str[val]);
		val++;
	}
}

/**
 * _eputchar - writes the character car to stderr
 * @car: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char car)
{
	static int val;
	static char buf[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || val >= WRITE_BUF_SIZE)
	{
		write(2, buf, val);
		val = 0;
	}
	if (car != BUF_FLUSH)
		buf[val++] = car;
	return (1);
}

/**
 * _putfd - writes the character car to given fd
 * @car: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char car, int fd)
{
	static int val;
	static char buf[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || val >= WRITE_BUF_SIZE)
	{
		write(fd, buf, val);
		val = 0;
	}
	if (car != BUF_FLUSH)
		buf[val++] = car;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int val = 0;

	if (!str)
		return (0);
	while (*str)
	{
		val += _putfd(*str++, fd);
	}
	return (val);
}
