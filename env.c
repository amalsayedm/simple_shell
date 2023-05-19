#include "shell.h"

/**
 * dom_val - value of an environ
 * @data: pointer
 * @env_name: environ name
 * Return: environ value
 */

char *dom_val(inputs_t *data, const char *env_name)
{
	link_t *node = data->env;
	char *val;

	while (node)
	{
		val = begain_with(node->str, env_name);
		if (val && *val)
			return (val);
		node = node->next;
	}
	return (NULL);
}

/**
 * occupied_domain - enviroment linked list
 * @data: pointer
 * Return:  0
 */

int occupied_domain(inputs_t *data)
{
	link_t *node = NULL;
	size_t el;

	for (el = 0; environ[el]; el++)
	addnode_to_end(&node, environ[el], 0);
	data->env = node;
	return (0);
}

/**
 * get_environ - returns the str array copy of our environ
 * @data: pointer
 * Return: Always 0
 */

char **get_environ(inputs_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = str_list(data->env);
		data->env_changed = 0;
	}
	return (data->environ);
}
