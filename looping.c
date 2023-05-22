#include "shell.h"

/**
 * shell_loop - main shell loop
 * @data: pointer
 * @av: the argument vector
 * Return: 0 or 1
 */

int shell_loop(inputs_t *data, char **av)
{
	ssize_t s = 0;
	int ret_BI = 0;

	while (s != -1 && ret_BI != -2)
	{
		clear_data(data);
		if (connected(data))
			_puts("$ ");
		putchar_stderr(BUF_FLUSH);
		s = get_input(data);
		if (s != -1)
		{
			set_data(av, data);
			ret_BI = buildIn_finder(data);
			if (ret_BI == -1)
				cmd_finder(data);
		}
		else if (connected(data))
			_putchar('\n');
		free_data(data, 0);
	}

	create_history(data);
	free_data(data, 1);
	if (!connected(data) &&
			data->status)
		exit(data->status);
	if (ret_BI == -2)
	{
		if (data->error_exit == -1)
			exit(data->status);
		exit(data->error_exit);
	}
	return (ret_BI);
}

/**
 * * buildIn_finder - finds a builtin
 * @data: pointer
 * Return: -1 = not found or-2 = exit or 0 =success or1 = found but no success
 */

int buildIn_finder(inputs_t *data)
{
	int result_builtIn = -1;
	int index;
	builtIn_t Built_In[] = {
		{"exit", exiting},
		{"env", domain},
		{"help", helper},
		{"history", archive},
		{"setenv", new_envioremt},
		{"unsetenv", remove_domain},
		{"cd", cur_cd},
		{"alias", alias},
		{NULL, NULL}
	};

	for (index = 0; Built_In[index].type; index++)
		if (_strcmp(data->av[0], Built_In[index].type) == 0)
		{
			data->count_line++;
			result_builtIn = Built_In[index].func(data);
			break;
		}
	return (result_builtIn);
}
