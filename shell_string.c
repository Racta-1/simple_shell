#include "shellheader.h"

/**
 **_strncpy - a function that copies a string
 *@des: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *des, char *src, int n)
{
	int i, j;
	char *s = des;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		des[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			des[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - a function that concatenates two strings
 *@des: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *des, char *src, int n)
{
	int i, j;
	char *s = des;

	i = 0;
	j = 0;
	while (des[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		des[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		des[i] = '\0';
	return (s);
}

/**
 **_strchr - a function that locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

