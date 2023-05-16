#include "shell.h"

/**
* check_abc - checks for alphabetic character
* @abc: character
* Return: 1 or 0
*/

int check_abc(int abc)
{
	if ((abc >= 'a' && abc <= 'z') ||
			(abc >= 'A' && abc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
* check_delim - checks if character is a delimeter
* @chars: the char to check
* @delim: the delimeter str
* Return: 1 if true, 0 if false
*/
int check_delim(char chars, char *delim)
{
	while (*delim)
		if (*delim++ == chars)
			return (1);
	return (0);
}

/**
 * _atoi - converts a str to an integer
 * @converter: the str to be converted
 * Return: 0 or convert numb
 */

int _atoi(char *converter)
{
	int index, exit;
	int s = 1, flag = 0;
	unsigned int result = 0;

	for (index = 0;  converter[index] != '\0' &&
			flag != 2; index++)
	{
		if (converter[index] == '-')
			s *= -1;
		if (converter[index] >= '0' && converter[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (converter[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (s == -1)
		exit = -result;
	else
		exit = result;
	return (exit);
}

