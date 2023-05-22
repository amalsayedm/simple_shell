#include "shell.h"

/**
 * exiting - exits shell program
 * @data: pointer
 * Return: exit
 */

int exiting(inputs_t *data)
{
	int leave;

	if (data->av[1])
	{
		leave = str_converter(data->av[1]);
		if (leave == -1)
		{
			data->status = 2;
			error_msg(data, "Illegal number: ");
			puts_str(data->av[1]);
			putchar_stderr('\n');
			return (1);
		}
		data->error_exit = str_converter(data->av[1]);
		return (-2);
	}
	data->error_exit = -1;
	return (-2);
}

/**
 * helper - changes the current directory
 * @data: pointer
 * Return:0
 */

int helper(inputs_t *data)
{
	char **ptr_arr;

	ptr_arr = data->av;
	_puts("hello , i'm help \n");
	if (0)
		_puts(*ptr_arr);
	return (0);
}

/**
 * archive - displays the history list
 * @data: pointer
 * Return: 0
 */

int archive(inputs_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * cur_cd - changes the current directory
 * @data: pointer
 * Return: 0
 */

int cur_cd(inputs_t *data)
{
	char *ptr, *poin, buffer[1024];
	int ret_ch;

	ptr = getcwd(buffer, 1024);
	if (!ptr)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->av[1])
	{
		poin = dom_val(data, "HOME=");
		if (!poin)
			ret_ch = chdir((poin = dom_val(data, "PWD=")) ? poin : "/");
		else
			ret_ch = chdir(poin);
	}
	else if (_strcmp(data->av[1], "-") == 0)
	{
		if (!dom_val(data, "OLDPWD="))
		{
			_puts(ptr);
			_putchar('\n');
			return (1);
		}
		_puts(dom_val(data, "OLDPWD=")), _putchar('\n');
		ret_ch =  chdir((poin = dom_val(data, "OLDPWD=")) ? poin : "/");
	}
	else
		ret_ch = chdir(data->av[1]);
	if (ret_ch == -1)
	{
		error_msg(data, "can't cd to ");
		puts_str(data->av[1]), putchar_stderr('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", dom_val(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* replace_hash - replaces first instance of '#' with '\0'
* @buf: pointer
* Return: void
*/

void replace_hash(char *buf)
{
int index;

for (index = 0; buf[index] != '\0'; index++)
if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
{
buf[index] = '\0';
break;
}
}
