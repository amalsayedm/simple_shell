#include "shell.h"


/**
 * sigintHandler - blocks ctrl-C
 * @num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * get_input - get commands
 * @data: parameter struct
 * @input: apointer to input
 * @len: pointer to length
 * Return: bytes read
 */
ssize_t get_input(inputs_t *data, char **input, size_t *len)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*input);
		*input = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = getline(input, &len_p, stdin);
#else
		read = _getline(data, input, &len_p);
#endif
		if (read > 0)
		{
			if ((*input)[read - 1] == '\n')
			{
				(*input)[read - 1] = '\0'; /* remove trailing newline */
				read--;
			}
			data->linecount_flag = 1;
			replace_hash(*input);
			history_list(data, *input, data->count_history++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = read;
				data->buf_cmd = input;
			}
		}
	}
	return (read);
}


/**
 * read_input - reads input
 * @data: parameter struct
 * @input: input buffer
 * @i: input size
 * Return: read count
 */
ssize_t read_input(inputs_t *data, char *input, size_t *i)
{
	ssize_t readc = 0;

	if (*i)
		return (0);
	readc = read(data->readfd, input, READ_BUF_SIZE);
	if (readc >= 0)
		*i = readc;
	return (readc);
}

/**
 * _getline - gets the next line
 * @data: input struct
 * @ptr: pointer of pointer to input
 * @length: size of preallocated ptr
 * Return: count
 */
int _getline(inputs_t *data, char **ptr, size_t *length)
{

	static size_t i, size;
	size_t k;
static char buf[READ_BUF_SIZE];
	ssize_t readc = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == size)
		i = size = 0;

	readc = read_input(data, buf, &size);
	if (readc == -1 || (readc == 0 && size == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : size;
	new_p = redistribute(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
