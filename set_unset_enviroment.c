#include "shell.h"

/**
 * _setenv - Initialize a new environment
 * @ev: str enviroment
 * @e_val: str "ev value"
 * @data: pointer
 * Return: 0
 */

int _setenv(char *ev, char *e_val, inputs_t *data)
{
	char *buf = NULL;
	link_t *node;
	char *ptr;

	if (!ev || !e_val)
		return (0);
	buf = malloc(_strlen(ev) + _strlen(e_val) + 2);

	if (!buf)
		return (1);
	_strcptry(buf, ev_val);
	_strcat(buf, "=");
	_strcat(buf, e_val);
	node = data->env;

	while (node)
	{
		ptr = begain_with(node->str, ev);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_to_end_node(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Remove environment
 * @ev: str enviroment
 * @data: pointer
 * Return: 1 or 0
 */

int _unsetenv(char *ev, inputs_t *data)
{
	link_t *node = data->env;
	size_t s = 0;
	char *ptr;

	if (!node || !ev)
		return (0);

	while (node)
	{
		ptr = begain_with(node->str, ev);
		if (ptr && *ptr == '=')
		{
			data->env_changed = delete_index_node(&(data->env), s);
			s = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		s++;
	}
	return (data->env_changed);
}
