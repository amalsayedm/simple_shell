#include "shell.h"

/**
 * _strcpy - copies string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int s = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[s])
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int size = 0;
	char *des;

	if (str == NULL)
		return (NULL);
	while (*str++)
		size++;
	des = malloc(sizeof(char) * (size + 1));
	if (!des)
		return (NULL);
	for (size++; size--;)
		des[size] = *--str;
	return (des);
}

/**
 *_puts - prints an input string
 *@str: the string
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
