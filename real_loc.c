#include "shell.h"

/**
 * redistribute - reallocates a block of memory
 * @ptr: pointer to previous memeory
 * @old_size: old memeory size
 * @new_size: new  memory size
 * Return: pointer to old memeory
 */
void *redistribute(void *ptr, unsigned int old_size, unsigned int new_size)
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
/**
 **_memset - fills memory with a constant byte
 *@s: pointer to the memory
 *@b: the byte to fill
 *@n: no of bytes
 *Return: pointer to the memory
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}
/**
 * free_str - frees a string of strings
 * @pp: the input pointer
 */
void free_str(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}
