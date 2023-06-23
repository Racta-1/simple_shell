#include "shellheader.h"

/**
 * _memset - a function that fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @val: the byte to fill *mem with
 * @num: the amount of bytes to be filled
 * Return: (mem) a pointer to the memory area mem
 */
char *_memset(char *mem, char val, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		mem[i] = val;
	return (mem);
}

/**
 * ffree - a function that frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - a function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

