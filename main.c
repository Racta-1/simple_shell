#include "shellheader.h"

/**
 * main - the main function (entry point)
 * @count: arg count
 * @vec: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int count, char **vec)
{
	info_t var[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (count == 2)
	{
		fd = open(vec[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(vec[0]);
				_eputs(": 0: Can't open ");
				_eputs(vec[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		var->readfd = fd;
	}
	populate_env_list(var);
	read_history(var);
	hsh(var, vec);
	return (EXIT_SUCCESS);
}

