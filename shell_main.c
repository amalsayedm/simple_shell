#include "shell.h"

/**
 * main - main function
 * @ac: argument count
 * @av: argument data

 * Return: 0 or 1
 */

int main(int ac, char **av)
{
	
	int fd = 2;
	inputs_t data[] = {{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0 }};

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_str(av[0]);
				puts_str(": 0: Can't open ");
				puts_str(av[1]);
				putchar_stderr('\n');
				putchar_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	occupied_domain(data);
	read_history(data);
	shell_loop(data, av);
	return (EXIT_SUCCESS);
}
