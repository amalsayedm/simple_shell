#include "shell.h"

/**
 * replace_token_var - replaces variable
 * @data: pointer
 * Return: 1 or 0
 */

int replace_token_var(inputs_t *data)
{
	int index = 0;
	link_t *node;

	for (index = 0; data->av[index]; index++)
	{
		if (data->av[index][0] != '$' || !data->av[index][1])
			continue;
		if (!_strcmp(data->av[index], "$?"))
		{
			replace_str(&(data->av[index]),
					_strdup(num_converter(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->av[index], "$$"))
		{
			replace_str(&(data->av[index]),
					_strdup(num_converter(getpid(), 10, 0)));
			continue;
		}
		node = begain_with_node(data->env, &data->av[index][1], '=');
		if (node)
		{
			replace_str(&(data->av[index]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_str(&data->av[index], _strdup(""));
	}
	return (0);
}

/**
 * replace_str - replaces str
 * @o: pointer
 * @n: new str
 * Return: 1 or 0
 */

int replace_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}

/**
 * replace_alias - replaces aliases
 * @data: poibter
 * Return: 1 or 0
 */

int replace_alias(inputs_t *data)
{
	int index;
	link_t *node;
	char *ptr;

	for (index = 0; index < 10; index++)
	{
		node = begain_with_node(data->alias, data->av[0], '=');
		if (!node)
			return (0);
		free(data->av[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		data->av[0] = ptr;
	}
	return (1);
}
