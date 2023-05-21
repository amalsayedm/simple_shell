#include "shell.h"

/**
 * alias - built in alias
 * @data: pointer
 * Return: 0
 */

int alias(inputs_t *data)
{
	int index = 0;
	char *ptr = NULL;
	link_t *node = NULL;

	if (data->ac == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; data->av[index]; index++)
	{
		ptr = _strchr(data->av[index], '=');
		if (ptr)
			set_alias(data, data->av[index]);
		else
			print_alias(begain_with_node(data->alias, data->av[index], '='));
	}
	return (0);
}

/**
 * print_alias - prints an alias
 * @node: alias node
 * Return: 0 or 1
 */

int print_alias(link_t *node)
{
	char *ptr = NULL;
	char *poi = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (poi = node->str; poi <= ptr; poi++)
			_putchar(*poi);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_alias - sets alias
 * @str:  str alias
 * @data: pointer
 * Return: 0 or 1
 */

int set_alias(char *str, inputs_t *data)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(data, str));
	unset_alias(data, str);
	return (addnode_to_end(&(data->alias), str, 0) == NULL);
}

/**
 * unset_alias - sets alias to str
 * @data: parameter struct
 * @str: str alias
 * Return: 0 or 1
 */

int unset_alias(inputs_t *data, char *str)
{
	char *ptr;
	char abc;
	int out_ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	abc = *ptr;
	*ptr = 0;
	out_ret = delete_node(&(data->alias),
			node_index(data->alias, begain_with_node(data->alias, str, -1)));
	*ptr = abc;
	return (out_ret);
}
