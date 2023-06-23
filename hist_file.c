#include "shellheader.h"

/**
 * get_history_file - a function that gets the history file
 * @var: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *var)
{
	char *buf, *dir;

	dir = _getenv(var, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - a function that creates a file, or appends to an existing file
 * @var: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *var)
{
	ssize_t fd;
	char *filename = get_history_file(var);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = var->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - a function that reads history from file
 * @var: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *var)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(var);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(var, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(var, buf + last, linecount++);
	free(buf);
	var->histcount = linecount;
	while (var->histcount-- >= HIST_MAX)
		delete_node_at_index(&(var->history), 0);
	renumber_history(var);
	return (var->histcount);
}

/**
 * build_history_list - a function that adds entry to a history linked list
 * @var: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *var, char *buf, int linecount)
{
	list_t *node = NULL;

	if (var->history)
		node = var->history;
	add_node_end(&node, buf, linecount);

	if (!var->history)
		var->history = node;
	return (0);
}

/**
 * renumber_history - a function that renumbers the history linked list after changes
 * @var: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *var)
{
	list_t *node = var->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (var->histcount = i);
}

