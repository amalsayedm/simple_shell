#include "shell.h"

/**
 * connected - check  if shell is interactive
 * @data: pointer
 * Return: 1 or 0
 */

int connected(inputs_t *data)
{
	/* isatty : test if fd is open file descriptor referring to a terminal*/
	/* STDIN_FILENO : the default standard input file descriptor number = 0*/
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}


/**
 * cmd_finder - finds a command in PATH
 * @data: pointer
 * Return: void
 */

void cmd_finder(inputs_t *data)
{
	char *path = NULL;
	int index, i;

	data->path = data->av[0];
	if (data->linecount_flag == 1)
	{
		data->count_line++;
		data->linecount_flag = 0;
	}
	for (index = 0, i = 0; data->arg[index]; index++)
		if (!check_delim(data->arg[index], " \t\n"))
			i++;
	if (!i)
		return;
	path = path_finder(data, dom_val(data, "PATH="), data->av[0]);
	if (path)
	{
		data->path = path;
		cmd_fork(data);
	}
	else
	{
		if ((connected(data) ||
					dom_val(data, "PATH=") ||
					data->av[0][0] == '/') &&
				cmd(data, data->av[0]))
			cmd_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			error_msg(data, "not found\n");
		}
	}
}


/**
 * cmd_fork - forks cmd
 * @data: pointer
 * Return: void
 */

void cmd_fork(inputs_t *data)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		/* perror : printd descriptive error msg to be*/
		/* stderr"standard error msg that is used to print the output*/
		/* on screen or windows terminal"*/
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* execve : causes the running program to be replaced with a new one*/
		if (execve
				(data->path, data->av, get_environ(data)) == -1)
		{
			free_data(data, 1);
			/* EACCES: permissin denied */
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		/* WIFEXITED : query status to see if child [rocess ended normally*/
		if (WIFEXITED(data->status))
		{
			/* WEXITSTATUS : macro queries the child termination satuts*/
			/* provided by wait and waitpid functioni*/
			/* it returns exit code*/
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				error_msg(data, "Permission denied\n");
		}
	}
}
