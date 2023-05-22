#include "shell.h"

/**
 * tok_str - splits string into words
 * @str: the string
 * @d: the delimeter
 * Return: pointer to an array of strings
 */

char **tok_str(char *str, char *d)
{
	char **ret;
	int i, j, k, s;
	int words_count = 0;


	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!check_delim(str[i], d) && (check_delim(str[i + 1], d) || !str[i + 1]))
			words_count++;

	if (words_count == 0)
		return (NULL);
	ret = malloc((1 + words_count) * sizeof(char *));
	if (!ret)
		return (NULL);
	for (i = 0, j = 0; j < words_count; j++)
	{
		while (check_delim(str[i], d))
			i++;
		k = 0;
		while (!check_delim(str[i + k], d) && str[i + k])
			k++;
		ret[j] = malloc((k + 1) * sizeof(char));
		if (!ret[j])
		{
			for (k = 0; k < j; k++)
				free(ret[k]);
			free(ret);
			return (NULL);
		}
		for (s = 0; s < k; s++)
			ret[j][s] = str[i++];
		ret[j][s] = 0;
	}
	ret[j] = NULL;
	return (ret);
}

/**
 * tok_str_b - splits a string into words
 * @s: the string
 * @b: the delimeter
 * Return: a pointer to an array of splited strings
 */
char **tok_str_b(char *s, char b)
{
	int i, j, k, l;
	int count = 0;
	char **ret;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != b && s[i + 1] == b) ||
			(s[i] != b && !s[i + 1]) || s[i + 1] == b)
			count++;
	if (count == 0)
		return (NULL);
	ret = malloc((1 + count) * sizeof(char *));
	if (!ret)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (s[i] == b && s[i] != b)
			i++;
		k = 0;
		while (s[i + k] != b && s[i + k] && s[i + k] != b)
			k++;
		ret[j] = malloc((k + 1) * sizeof(char));
		if (!ret[j])
		{
			for (k = 0; k < j; k++)
				free(ret[k]);
			free(ret);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			ret[j][l] = s[i++];
		ret[j][l] = 0;
	}
	ret[j] = NULL;
	return (ret);
}
