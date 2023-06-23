#include "shellheader.h"

/**
 * **strtow - a function that splits a string into words. Repeat delimiters are ignored
 * @var: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *var, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (var == NULL || var[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; var[i] != '\0'; i++)
		if (!is_delim(var[i], d) && (is_delim(var[i + 1], d) || !var[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(var[i], d))
			i++;
		k = 0;
		while (!is_delim(var[i + k], d) && var[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = var[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - a function that splits a string into words
 * @var: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *var, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (var == NULL || var[0] == 0)
		return (NULL);
	for (i = 0; var[i] != '\0'; i++)
		if ((var[i] != d && var[i + 1] == d) ||
				    (var[i] != d && !var[i + 1]) || var[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (var[i] == d && var[i] != d)
			i++;
		k = 0;
		while (var[i + k] != d && var[i + k] && var[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = var[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

