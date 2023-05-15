#include "shell.h"

/**
 * set_data - get inputs_t data
 * @data: pointer
 * @av: argument vector
 * Return : void
 */

void set_data(char **av, inputs_t *data)
{
	int abc = 0;

	data->file_name = av[0];

	if (data->arg)
	{
		data->av = tok_str(data->arg, " \t");
		if (!data->av)
		{
			data->av = malloc(sizeof(char *) * 2);
			if (data->av)
			{
				data->av[0] = _strdup(data->arg);
				data->av[1] = NULL;
			}
		}
		for (abc = 0; data->av && data->av[abc]; abc++)
			;
		data->ac = abc;
		replace_alias(data);
		replace_token_var(data);
	}
}	


/**
 * clear_data - load inputs_t
 * @data: pointer
 * Return : void
 */

void clear_data(inputs_t *data)
{
	data->arg = NULL;
	data->av = NULL;
	data->ac = 0;
	data->path = NULL;
}

/**
 * free_data - free inputs_t
 * @data: pointer
 * @free_all: check all feilds are free
 * Return : void
 */

void free_data(inputs_t *data, int free_all)
{
	free_str(data->av);
	data->av = NULL;
	data->path = NULL;

	if (free_all)
	{
		if (!data->buf_cmd)
			free(data->arg);
		if (data->env)
			list_free(&(data->env));
		if (data->history)
			list_free(&(data->history));
		if (data->alias)
			list_free(&(data->alias));
		free_str(data->environ);
		data->environ = NULL;
		free_ptr((void **)data->buf_cmd);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}

