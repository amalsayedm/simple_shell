#include"shell.h"
/**
 * history_list - adds  to history list
 * @data: struct
 * @str: string
 * @line_count: the history count
 * Return: Always 0
 */
int history_list(inputs_t *data, char *str, int line_count)
{
	link_t *list = NULL;

	if (data->history)
		list = data->history;
	add_node_end(&list, str, line_count);

	if (!data->history)
		data->history = list;
	return (0);
}

/**
 * get_history - gets the history file
 * @data: input struct
 * Return: string containg history
 */

char *get_history(inputs_t *data)
{
	char *str, *folder;

	folder = dom_val(data, "HOME=");
	if (!folder)
		return (NULL);
	str = malloc(sizeof(char) * (_strlen(folder) + _strlen(HIST_FILE) + 2));
	if (!str)
		return (NULL);
	str[0] = 0;
	_strcpy(str, folder);
	_strcat(str, "/");
	_strcat(str, HIST_FILE);
	return (str);
}
