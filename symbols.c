#include"shell.h"


/**
 * chain_tester -checks char if it is chain delimeter
 * @data: pointer
 * @buf: buffer
 * @ptr: pointer
 * Return: 1 or 0
 */

int chain_tester(inputs_t *data, char *buf, size_t *ptr)
{
	size_t s = *ptr;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		data->type_cmd = CMD_OR;
	}
	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		data->type_cmd = CMD_AND;
	}
	else if (buf[s] == ';')
	{
		buf[s] = 0;
		data->type_cmd = MD_CHAIN;
	}
	else
		return (0);
	*ptr = s;
	return (1);
}

/**
 * check_chain - checks last status and if it should channing
 * @data: pointer
 * @buf: the char buffer
 * @ptr: address of current position in buf
 * @index: starting position in buf
 * @lg: length of buf
 * Return: Void
 */

void check_chain(inputs_t *data, char *buf, size_t *ptr,
		 size_t index, size_t lg)
{
	size_t s = *ptr;

	if (data->type_cmd == CMD_AND)
	{
		if (data->status)
		{
			buf[index] = 0;
			s = lg;
		}
	}
	if (data->type_cmd == CMD_OR)
	{
		if (!data->status)
		{
			buf[index] = 0;
			s = lg;
		}
	}
	*ptr = s;
}
