#include "shellheader.h"

/**
 * bfree - a function that frees a pointer and NULLs the address
 * @val: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **val)
{
	if (val && *val)
	{
		free(*val);
		*val = NULL;
		return (1);
	}
	return (0);
}

