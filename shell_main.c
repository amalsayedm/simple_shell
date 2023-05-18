#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: vector
 * Return: 0 or 1
 */

int main(int ac, char **av)
{
	inputs_t data[] = { data_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_str(av[0]);
				puts_str(": 0: Can't open ");
				puts_str(av[1]);
				putchar_stderr('\n');
				putchar_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	occupied_domain(data);
	read_history(data);
	shell_loop(data, av);
	return (EXIT_SUCCESS);
}

/**
 * shell_loop - main shell loopi
 * @av: the argument vector
 * @data: pointer
 * Return: 0 or 1
 */

int shell_loop(char **av, inputs_t *data)
{
	ssize_t s = 0;
	int returnedBI = 0;

	while (s != -1 && returnedBI != -2)
	{
		clear_data(data);
		if (connected(data))
			_puts("$ ");
		putchar_stderr(BUF_FLUSH);
		s = get_input(data);
		if (s != -1)
		{
			set_data(data, av);
			returnedBI = buildIn_finder(data);
			if (returnedBI == -1)
			{
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
	if (returnedBI == -2)
	{
		if (data->error_exit == -1)
			exit(data->status);
		exit(data->error_exit);
	}
	return (returnedBI);
}

/**
 * buildIn_finder - finds a builtin
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
		{"cd", _mycd},
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
