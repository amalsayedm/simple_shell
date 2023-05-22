#include "shell.h"

/**
 * recall_history_list - renumbers history
 * @data: struct
 * Return: the new histroy count
 */
int recall_history_list(inputs_t *data)
{
	link_t *list = data->history;
	int index = 0;

	while (list)
	{
		list->num = index++;
		list = list->next;
	}
	return (data->count_history = index);
}

/**
 * create_history - write to  afile
 * @data:  struct
 * Return: 1 on success or -1 otherwise
 */
int create_history(inputs_t *data)
{
	ssize_t fd;
	char *file = get_history(data);
	link_t *link = NULL;

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (link = data->history; link; link = link->next)
	{
		puts_str_fd(link->str, fd);
		puts_fd('\n', fd);
	}
	puts_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @data: the struct
 * Return: file size
 */
int read_history(inputs_t *data)
{
	int index, count = 0,  last = 0;
	ssize_t fd, rd, filesize = 0;
	struct stat st;
	char *str = NULL, *filename = get_history(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	str = malloc(sizeof(char) * (filesize + 1));
	if (!str)
		return (0);
	rd = read(fd, str, filesize);
	str[filesize] = 0;
	if (rd <= 0)
		return (free(str), 0);
	close(fd);
	for (index = 0; index < filesize; index++)
		if (str[index] == '\n')
		{
			str[index] = 0;
			build_history_list(data, str + last, count++);
			last = index + 1;
		}
	if (last != index)
		recall_history_list(data, str + last, count++);
	free(str);
	data->count_history = count;
	while (data->count_history-- >= HIST_MAX)
		addnode_to_end(&(data->history), 0);
	recall_history_list(data);
	return (data->count_history);
}
