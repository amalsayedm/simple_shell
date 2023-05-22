#include "shell.h"

/**
 * str_converter - converts a str to an integer
 * @str: str will be converted
 * Return: 0 or -1
 */

int str_converter(char *str)
{
	int index = 0;
	unsigned long int rt = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			rt *= 10;
			rt += (str[index] - '0');
			if (rt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rt);
}

/**
 * num_converter - converter function
 * @base: base
 * @flags: argument flags
 * @num: number
 * Return: str
 */

char *num_converter(int base, int flags, long int num)
{
	static char *arr, buffer[50];
	char *ptr, sign = 0;
	unsigned long ns = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		ns = -num;
		sign = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = arr[n % base];
		ns /= base;
	}while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * puts_str_fd - prints str
 * @fd: file descriptor to write
 * @str: str
 * Return: number of chars
 */

int puts_str_fd(int fd, char *str)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += puts_fd(*str++, fd);
	}
	return (index);
}

/**
 * puts_fd - char to be given to fd
 * @fd:  file descriptor
 * @abc: character to print
 * Return: 1 or-1
 */

int puts_fd(int fd, char abc)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (abc == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (abc != BUF_FLUSH)
		buf[index++] = abc;
	return (1);
}
