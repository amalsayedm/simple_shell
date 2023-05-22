#include "shell.h"
#include <sys/stat.h>


/**
 * check_cmd - checks if command is an executable command
 * @data: the data struct
 * @path: path to the file
 * Return: 1 or 0 otherwise
 */
int check_cmd(inputs_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (S_ISREG(st.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * get_path - finds command in path
 * @data: the struct
 * @path: the PATH string
 * @cmd: the command
 * Return: full path of command
 */
char *get_path(inputs_t *data, char *path, char *cmd)
{
	int i = 0, current = 0;
	char *str;

	if (!path)
		return (NULL);
	if ((_strlen(cmd) > 2) && begain_with(cmd, "./"))
	{
		if (check_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path[i] || path[i] == ':')
		{
			str = duplicate_chars(path, current, i);
			if (!*str)
				_strcat(str, cmd);
			else
			{
				_strcat(str, "/");
				_strcat(str, cmd);
			}
			if (check_cmd(data, str))
				return (str);
			if (!path[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * duplicate_chars - duplicates characters
 * @path: the PATH
 * @startindex: start index
 * @lastindex: last index
 * Return: pointer to new str
 */
char *duplicate_chars(char *path, int startindex, int lastindex)
{

	int i = 0, j = 0;
static char str[1024];
	for (j = 0, i = startindex; i < lastindex; i++)
		if (path[i] != ':')
			str[j++] = path[i];
	str[j] = 0;
	return (str);
}
