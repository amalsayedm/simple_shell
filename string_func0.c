#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string
 * Return: the length of string
 */
int _strlen(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;

	return (index);
}

/**
 * _strcmp - compare two strings
 * @s1: the first string
 * @s2: the second string
 * Return: -1 if s1 < s2, +1if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begain_with - checks if string starts with another substring
 * @mainstr: string to search
 * @substr: the substring
 * Return: address of next char of input string
 */
char *begain_with(const char *mainstr, const char *substr)
{
	while (*substr)
		if (*substr++ != *mainstr++)
			return (NULL);
	return ((char *)mainstr);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
