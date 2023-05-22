#include "shell.h"

/**
 * error_msg - prints an error message
 * @data: pointer
 * @estr: str containing specified error type
 * Return: void
 */

void error_msg(inputs_t *data, char *estr)
{
	puts_str(data->file_name);
	puts_str(": ");
	decimal_10(data->count_line, STDERR_FILENO);
	puts_str(": ");
	puts_str(data->av[0]);
	puts_str(": ");
	puts_str(estr);
}

/**
 * puts_str - prints an input str
 * @str: str to print
 * Return: void
 */

void puts_str(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		putchar_stderr(str[index]);
		index++;
	}
}

/**
 * putchar_stderr - character to stderr
 * @abc: The character to print
 * Return: 1  or -1
 */

int putchar_stderr(char abc)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (abc == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (abc != BUF_FLUSH)
		buf[index++] = abc;
	return (1);
}

/**
 * decimal_10 -  prints a decimal (integer base 10)
 * @input: intiger input
 * @fd:  file descriptor to write to
 * Return: number of characters printed
 */

int decimal_10(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index;
	int sum = 0;
	unsigned int abc;
	unsigned int present;

	if (fd == STDERR_FILENO)
		__putchar = putchar_stderr;
	if (input < 0)
	{
		abc = -input;
		__putchar('-');
		sum++;
	}
	else
		abc = input;
	present = abc;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (abc / index)
		{
			__putchar('0' + present / index);
			sum++;
		}
		present %= index;
	}
	__putchar('0' + present);
	sum++;
	return (sum);
}

