#include "shell.h"

/**
 * free_ptr - frees a pointer
 * @ptr: the pointer to free
 * Return: 1 or 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
